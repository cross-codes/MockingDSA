#include <algorithm> // IWYU pragma: keep
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

using usize = std::size_t;
using ssize = std::ptrdiff_t;

using u32   = std::uint32_t;
using u64   = std::uint64_t;
using i64   = std::int64_t;

using i128  = __int128;
using u128  = unsigned __int128;

namespace StandardIODevice
{

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1 << 20
#endif

#if (__cpp_nontype_template_parameter_class ||                                 \
     (__cpp_nontype_template_args >= 201911L))
template <std::size_t N> struct fixed_string
{
  std::array<char, N> buf;

  constexpr fixed_string(char const s[]) noexcept
  {
    for (size_t i = 0; i < N; i++)
      buf[i] = s[i];
  }

  constexpr auto begin() noexcept
  {
    return buf.begin();
  }
  constexpr auto end() noexcept
  {
    return buf.end();
  }
  constexpr auto begin() const noexcept
  {
    return buf.begin();
  }
  constexpr auto end() const noexcept
  {
    return buf.end();
  }
};

template <size_t N> fixed_string(char const (&)[N]) -> fixed_string<N - 1>;
#endif

struct OutputWriter
{
  std::array<char, BUFFER_SIZE> buffer;
  size_t idx = 0;
  int const fd;

  [[nodiscard]] explicit OutputWriter(int const fd) noexcept : fd(fd)
  {
  }
  [[nodiscard]] explicit OutputWriter(char const f[]) noexcept
      : fd(open(f, O_WRONLY | O_CREAT, 0644))
  {
  }

  OutputWriter(OutputWriter const &)            = delete;
  OutputWriter &operator=(OutputWriter const &) = delete;

  void flush() noexcept
  {
    [[maybe_unused]] ssize_t rc = write(fd, buffer.data(), idx);
    assert(rc >= 0);
    idx = 0;
  }

  void flush_if(size_t x) noexcept
  {
#ifndef NO_AUTO_FLUSH
    if (buffer.size() - idx < x)
      flush();
#endif
  }

  OutputWriter &operator<<(char const c) noexcept
  {
    flush_if(1);
    buffer[idx++] = c;
    return *this;
  }

  template <class T, class = std::enable_if_t<std::is_integral<T>::value>,
            class unsT = typename std::make_unsigned<T>::type>
  OutputWriter &operator<<(T const a) noexcept
  {
    std::array<char,
               (long)(sizeof(T) * 2.40823996531) + 1 + std::is_signed<T>::value>
        d;
    uint8_t i = d.size();

    static_assert(d.size() <= 256);

    unsT u = a;

    if constexpr (std::is_signed<T>::value)
      if (std::signbit(a))
        u = -u;

    do
    {
      d[--i] = u % 10 + '0';
      u /= 10;
    } while (u);

    if constexpr (std::is_signed<T>::value)
      if (std::signbit(a))
        d[--i] = '-';

    flush_if(d.size() - i);
    memcpy(&buffer[idx], &d[i], d.size() - i);
    idx += d.size() - i;
    return *this;
  }

  OutputWriter &operator<<(char const s[]) noexcept
  {
    size_t len = strlen(s);
    flush_if(len);
    memcpy(&buffer[idx], s, len);
    idx += len;
    return *this;
  }

  OutputWriter &operator<<(std::string_view const s) noexcept
  {
    flush_if(s.size());
    memcpy(&buffer[idx], s.data(), s.size());
    idx += s.size();
    return *this;
  }

  OutputWriter &operator<<(std::string const &s) noexcept
  {
    flush_if(s.size());
    memcpy(&buffer[idx], s.data(), s.size());
    idx += s.size();
    return *this;
  }

  template <class T, class = std::enable_if_t<std::is_floating_point<T>::value>>
  OutputWriter &operator<<(T f) noexcept
  {
    constexpr size_t precision = 6;

    if constexpr (std::is_signed<T>::value)
      if (std::signbit(f))
      {
        *this << '-';
        f *= -1;
      }

    int e = 0;
    while (f < 1)
    {
      f *= 10;
      e -= 1;
    }
    while (f >= 10)
    {
      f /= 10;
      e += 1;
    }

    if (e <= -5 || e >= 6)
    {
      flush_if(precision + 2);
      for (size_t i = 0; i < precision; i++)
      {
        if (i == 1)
          buffer[idx++] = '.';

        buffer[idx++] = int(f) + '0';
        f -= int(f);
        f *= 10;
      }

      buffer[idx++] = 'e';
      return *this << e;
    }
    else
    {
      f *= pow(10, e);
      return *this << (unsigned)f << '.'
                   << (unsigned)(pow(10, precision - e - 1) *
                                 (f - (unsigned)f));
    }
  }

  OutputWriter &operator<<(void *p) noexcept
  {
    constexpr char const *digits = "0123456789abcdef";

    std::array<char, 2 * sizeof(void *) + 2> d;
    uint8_t i = d.size();

    static_assert(d.size() <= 256);
    static_assert(sizeof(size_t) == sizeof(void *));

    do
    {
      d[--i] = digits[(size_t)p & 0xF];
      p      = (void *)((size_t)p >> 4);
    } while (p);

    d[--i] = 'x';
    d[--i] = '0';

    flush_if(d.size() - i);
    memcpy(&buffer[idx], &d[i], d.size() - i);
    idx += d.size() - i;

    return *this;
  }

#if (__cpp_nontype_template_parameter_class ||                                 \
     (__cpp_nontype_template_args >= 201911L))
  template <fixed_string s, class... T> void fmt(T &&...v) noexcept
  {
    static_assert(std::count(s.begin(), s.end(), '%') == sizeof...(T),
                  "Number of parameters does not match format string");

    auto pos                           = s.begin();

    [[maybe_unused]] auto const helper = [this, &pos](auto &&v) {
      auto npos = std::find(pos, s.end(), '%');
      *this << std::string_view(pos, npos);
      *this << std::forward<decltype(v)>(v);
      pos = npos + 1;
    };

    (helper(std::forward<T>(v)), ...);
    *this << std::string_view(pos, s.end());
  }
#endif
};

constexpr static auto is_digit = [] {
  std::array<bool, 256> is_digit{};
  for (char c = '0'; c <= '9'; c++)
    is_digit[c] = true;
  return is_digit;
}();

struct InputReader
{
  std::array<char, BUFFER_SIZE> buffer;
  size_t idx = 0, size = 0;
  int const fd;

  [[nodiscard]] explicit InputReader(int const fd) noexcept : fd(fd)
  {
  }
  [[nodiscard]] explicit InputReader(char const f[]) noexcept
      : fd(open(f, O_RDONLY))
  {
  }
  InputReader(InputReader const &)            = delete;
  InputReader &operator=(InputReader const &) = delete;

  void flush() noexcept
  {
    if (idx == size)
    {
      ssize_t s = read(fd, buffer.data(), buffer.size());
      assert(s >= 0);
      size = s;
      idx  = 0;
    }
  }

  InputReader &operator>>(char &c) noexcept
  {
    flush();
    c = buffer[idx++];
    return *this;
  }

  template <class T, class = std::enable_if_t<std::is_integral<T>::value>>
  InputReader &operator>>(T &i) noexcept
  {
    while (flush(), buffer[idx] <= 32)
      idx++;

    bool sign = false;
    if constexpr (std::is_signed<T>::value)
      if (buffer[idx] == '-')
      {
        sign = 1;
        idx++;
      }

    i = 0;
    while (flush(), is_digit[buffer[idx]])
      i = 10 * i + buffer[idx++] - '0';

    if constexpr (std::is_signed<T>::value)
      if (sign)
        i *= -1;

    return *this;
  }
};
} // namespace StandardIODevice

StandardIODevice::InputReader consoleIn(STDIN_FILENO);
StandardIODevice::OutputWriter consoleOut(STDOUT_FILENO);
StandardIODevice::OutputWriter consoleErr(STDERR_FILENO);

namespace _RangeUpdateQueries
{

struct Algebra
{
private:
  Algebra();
  constexpr inline static double EPSILON_{1E-6};
  constexpr inline static int SIEVE_30_{~((1 << 1) | (1 << 7) | (1 << 11) |
                                          (1 << 13) | (1 << 17) | (1 << 19) |
                                          (1 << 23) | (1 << 29))};
  constexpr inline static std::int64_t FLOOR_SQRT_MAX_{3037000499LL};
  constexpr inline static std::uint64_t MOD{
      static_cast<std::uint64_t>(1e9 + 7)};

  inline static const std::vector<std::vector<std::int64_t>>
      millerRabinBaseSets_ = {
          {291830, 126401071349994536LL},
          {885594168, 725270293939359937LL, 3569819667048198375LL},
          {273919523040LL, 15, 7363882082LL, 992620450144556LL},
          {47636622961200LL, 2, 2570940, 211991001, 3749873356LL},
          {7999252175582850LL, 2, 4130806001517LL, 149795463772692060LL,
           186635894390467037LL, 3967304179347715805LL},
          {585226005592931976LL, 2, 123635709730000LL, 9233062284813009LL,
           43835965440333360LL, 761179012939631437LL, 1263739024124850375LL},
          {INT64_MAX, 2, 325, 9375, 28178, 450775, 9780504, 1795265022}};

  constexpr inline static int compare_(std::int64_t a, std::int64_t b)
  {
    std::int64_t flippedA{flip(a)}, flippedB{flip(b)};

    if (flippedA < flippedB)
      return -1;
    else if (flippedA > flippedB)
      return 1;
    else
      return 0;
  }

  constexpr inline static std::int64_t smallMulMod_(std::int64_t a,
                                                    std::int64_t b,
                                                    std::int64_t m)
  {
    return (a * b) % m;
  }

  constexpr inline static std::int64_t smallSquareMod_(std::int64_t a,
                                                       std::int64_t m)
  {
    return (a * a) % m;
  }

  constexpr inline static std::int64_t smallPowMod_(std::int64_t a,
                                                    std::int64_t p,
                                                    std::int64_t m)
  {
    std::int64_t res{1LL};
    for (; p != 0; p >>= 1)
    {
      if ((p & 1) != 0)
      {
        res = smallMulMod_(res, a, m);
      }
      a = smallSquareMod_(a, m);
    }
    return res;
  }

  constexpr inline static std::int64_t largePlusMod_(std::int64_t a,
                                                     std::int64_t b,
                                                     std::int64_t m)
  {
    return (a >= m - b) ? (a + b - m) : (a + b);
  }

  constexpr inline static std::int64_t largeTimes2ToThe32Mod_(std::int64_t a,
                                                              std::int64_t m)
  {
    int remainingPowersOf2{32};
    do
    {
      int shift{std::min(remainingPowersOf2, __builtin_clzll(a))};
      a = remainder(a << shift, m);
      remainingPowersOf2 -= shift;
    } while (remainingPowersOf2 > 0);
    return a;
  }

  constexpr inline static std::int64_t largeMulMod_(std::int64_t a,
                                                    std::int64_t b,
                                                    std::int64_t m)
  {
    std::int64_t aHi{a >> 32};
    std::int64_t bHi{b >> 32};
    std::int64_t aLo{a & 0xFFFFFFFFLL};
    std::int64_t bLo{b & 0xFFFFFFFFLL};
    std::int64_t result{largeTimes2ToThe32Mod_(aHi * bHi, m)};
    result += aHi * bLo;
    if (result < 0)
    {
      result = remainder(result, m);
    }
    result += aLo * bHi;
    result = largeTimes2ToThe32Mod_(result, m);
    return largePlusMod_(result, remainder(aLo * bLo, m), m);
  }

  constexpr inline static std::int64_t largeSquareMod_(std::int64_t a,
                                                       std::int64_t m)
  {
    std::int64_t aHi{a >> 32};
    std::int64_t aLo{a & 0xFFFFFFFFLL};
    std::int64_t result{largeTimes2ToThe32Mod_(aHi * aHi, m)};
    std::int64_t hiLo{aHi * aLo * 2};
    if (hiLo < 0)
      hiLo = remainder(hiLo, m);
    result += hiLo;
    result = largeTimes2ToThe32Mod_(result, m);
    return largePlusMod_(result, remainder(aLo * aLo, m), m);
  }

  constexpr inline static std::int64_t largePowMod_(std::int64_t a,
                                                    std::int64_t p,
                                                    std::int64_t m)
  {
    std::int64_t res{1LL};
    for (; p != 0; p >>= 1)
    {
      if (p & 1)
        res = largeMulMod_(res, a, m);
      a = largeSquareMod_(a, m);
    }

    return res;
  }

  inline static bool testWitnessSmall_(std::int64_t base, std::int64_t n)
  {
    int r{__builtin_ctzll(n - 1)};
    std::int64_t d{(n - 1) >> r};
    base %= n;
    if (base == 0)
      return true;

    std::int64_t a = smallPowMod_(base, d, n);
    if (a == 1)
      return true;
    int j{};
    while (a != n - 1)
    {
      if (++j == r)
        return false;
      a = smallSquareMod_(a, n);
    }

    return true;
  }

  inline static bool testWitnessLarge_(std::int64_t base, std::int64_t n)
  {
    int r{__builtin_ctzll(n - 1)};
    std::int64_t d{(n - 1) >> r};
    base %= n;
    if (base == 0)
      return true;

    std::int64_t a = largePowMod_(base, d, n);
    if (a == 1)
      return true;
    int j{};
    while (a != n - 1)
    {
      if (++j == r)
        return false;
      a = largeSquareMod_(a, n);
    }

    return true;
  }

  constexpr inline static auto exGCD_(int a, int b, int &x, int &y) -> int
  {
    if (b == 0)
    {
      x = 1;
      y = 0;
      return a;
    }

    int x1, y1;
    int d = exGCD_(b, a % b, x1, y1);
    x     = y1;
    y     = x1 - y1 * (a / b);
    return d;
  }

public:
  constexpr inline static std::int64_t flip(std::int64_t a)
  {
    return a ^ INT64_MIN;
  }

  constexpr inline static int mulMod(int a, int b, int m)
  {
    return static_cast<int>(smallMulMod_(a, b, m));
  }

  constexpr inline static int modPow(int n, int p, int m)
  {
    std::int64_t result{1LL};
    for (std::int64_t i = 1, j = n; i <= p; i <<= 1, j = j * j % m)
    {
      if (i & p)
        result = result * j % m;
    }

    return static_cast<int>(result);
  }

  constexpr inline static int coprimeModInv(int n, int m)
  {
    return modPow(n, m - 2, m);
  }

  inline static int log2(std::int64_t n)
  {
    return (n == 0) ? 0 : 63 - __builtin_clzll(n);
  }

  constexpr inline static int ceilLog2(std::int64_t n)
  {
    return (n == 1) ? 1 : 64 - __builtin_clzll(n - 1);
  }

  constexpr inline static bool equal(double a, double b)
  {
    return std::abs(a - b) < EPSILON_;
  }

  constexpr inline static bool equal0(double a)
  {
    return std::abs(a) < EPSILON_;
  }

  static std::unique_ptr<double[]> solveLinear(double a, double b, double c,
                                               double d, double e, double f)
  {
    double D{a * e - b * d};
    double Dx{c * e - b * f};
    double Dy{a * f - c * d};

    if (equal0(D))
    {
      std::size_t size = equal0(Dx) && equal0(Dy) ? 1 : 0;
      std::unique_ptr<double[]> result(new double[size]);
      std::memset(result.get(), 0x00, sizeof(int) * size);
      return result;
    }
    else
    {
      std::unique_ptr<double[]> result(new double[2]);
      result[0] = Dx / D, result[1] = Dy / D;
      return result;
    }
  }

  inline static std::unique_ptr<double[]> solveQuadratic(double a, double b,
                                                         double c)
  {
    double delta{b * b - 4 * a * c};
    if (equal0(delta))
    {
      std::unique_ptr<double[]> result(new double[1]);
      result[0] = -b / (a * 2);
      return result;
    }
    else if (delta < 0)
    {
      std::unique_ptr<double[]> result(new double[1]);
      result[0] = 0;
      return 0;
    }
    else
    {
      double a2{a * 2};
      double x{(-b / a2)};
      double y{std::sqrt(delta) / a2};

      std::unique_ptr<double[]> result(new double[2]);
      result[0] = x + y, result[1] = x - y;

      return result;
    }
  }

  constexpr inline static std::int64_t remainder(std::int64_t dividend,
                                                 std::int64_t divisor)
  {
    if (divisor < 0)
    {
      if (compare_(dividend, divisor) < 0)
        return dividend;
      else
        return dividend - divisor;
    }

    if (dividend >= 0)
      return dividend % divisor;

    std::int64_t quotient{((dividend >> 1) / divisor) << 1};
    std::int64_t rem{dividend - quotient * divisor};
    return rem - (compare_(rem, divisor) >= 0 ? divisor : 0);
  }

  inline static bool isPrime(std::int64_t n)
  {
    if (n < 2)
      return false;

    if (n < 66)
    {
      constexpr std::int64_t mask{
          (1LL << (2 - 2)) | (1LL << (3 - 2)) | (1LL << (5 - 2)) |
          (1LL << (7 - 2)) | (1LL << (11 - 2)) | (1LL << (13 - 2)) |
          (1LL << (17 - 2)) | (1LL << (19 - 2)) | (1LL << (23 - 2)) |
          (1LL << (29 - 2)) | (1LL << (31 - 2)) | (1LL << (37 - 2)) |
          (1LL << (41 - 2)) | (1LL << (43 - 2)) | (1LL << (47 - 2)) |
          (1LL << (53 - 2)) | (1LL << (59 - 2)) | (1LL << (61 - 2))};
      return ((mask >> (static_cast<int>(n) - 2)) & 1) != 0;
    }

    if (SIEVE_30_ & (1 << (n % 30)))
      return false;

    if (n % 7 == 0 || n % 11 == 0 || n % 13 == 0)
      return false;

    if (n < 17 * 17)
      return true;

    for (std::vector<std::int64_t> baseSet : millerRabinBaseSets_)
    {
      if (n <= baseSet[0])
      {
        bool small = n <= FLOOR_SQRT_MAX_;
        if (small)
        {
          for (std::size_t i = 1; i < baseSet.size(); i++)
          {
            if (!testWitnessSmall_(baseSet[i], n))
              return false;
          }
        }
        else
        {
          for (std::size_t i = 1; i < baseSet.size(); i++)
          {
            if (!testWitnessLarge_(baseSet[i], n))
              return false;
          }
        }
      }

      return true;
    }

    throw new std::runtime_error("Assertion failed");
  }

  constexpr inline static std::uint64_t fibonnaciNumber(
      std::uint64_t n, std::uint64_t modulus = MOD)
  {
    if (n == 1)
      return 1ULL;

    std::uint64_t a{1U}, b{0U}, p{0U}, q{1U};
    std::uint64_t aq, qq;
    while (n > 0)
    {
      if (n & 1)
      {
        aq = (a * q) % modulus;
        a  = ((((b * q) % modulus + aq) % modulus) + (a * p) % modulus) %
            modulus;
        b = ((b * p) % modulus + aq) % modulus;
        n--;
      }
      else
      {
        qq = (q * q) % modulus;
        q  = ((2 * p * q) % modulus + qq) % modulus;
        p  = ((p * p) % modulus + qq) % modulus;
        n /= 2;
      }
    }

    return b % modulus;
  }

  constexpr inline static auto solveDiophantine(int a, int b, int c, int &x,
                                                int &y, int &g) -> bool
  {
    g = exGCD_(std::abs(a), std::abs(b), x, y);
    if (c % g)
      return false;

    x *= c / g;
    y *= c / g;
    if (a < 0)
      x = -x;
    if (b < 0)
      y = -y;

    return true;
  }
};

template <typename T> struct SegmentTree
{
private:
  std::size_t offset_;
  std::unique_ptr<T[]> tree_;

  std::function<T(const T &, const T &)> function_;
  T defaultValue_;

public:
  SegmentTree(const std::unique_ptr<T[]> &array, std::size_t n, T defaultValue,
              std::function<T(const T &, const T &)> function)
      : offset_(1LL << Algebra::ceilLog2(n)),
        tree_(std::make_unique<T[]>(offset_ << 1)), function_(function),
        defaultValue_(defaultValue)
  {
    std::copy(&array[0], &array[n], &tree_[offset_]);

    std::size_t i = offset_;
    while (i != 1)
    {
      std::size_t j = i;
      while (j < i << 1)
      {
        tree_[j >> 1] = function_(tree_[j], tree_[j + 1]);
        j += 2;
      }
      i >>= 1;
    }
  }

  template <std::size_t N>
  SegmentTree(const std::array<T, N> &array, T defaultValue,
              std::function<T(const T &, const T &)> function)
      : offset_(1LL << Algebra::ceilLog2(N)),
        tree_(std::make_unique<T[]>(offset_ << 1)), function_(function),
        defaultValue_(defaultValue)
  {
    std::copy(array.begin(), array.end(), &tree_[offset_]);

    std::size_t i = offset_;
    while (i != 1)
    {
      std::size_t j = i;
      while (j < i << 1)
      {
        tree_[j >> 1] = function_(tree_[j], tree_[j + 1]);
        j += 2;
      }
      i >>= 1;
    }
  }

  void setAtIndex(std::size_t index, T value)
  {
    index += offset_;
    tree_[index] = value;

    while (index != 1)
    {
      tree_[index >> 1] = function_(tree_[index], tree_[index ^ 1]);
      index >>= 1;
    }
  }

  T queryRange(std::size_t fromIdx, std::size_t pastEndIdx)
  {
    fromIdx += offset_, pastEndIdx += offset_;

    T result{defaultValue_};
    while (fromIdx < pastEndIdx)
    {
      if (fromIdx & 1)
        result = function_(result, tree_[fromIdx++]);
      if (pastEndIdx & 1)
        result = function_(result, tree_[--pastEndIdx]);

      fromIdx >>= 1, pastEndIdx >>= 1;
    }

    return result;
  }
};

auto run() -> void
{
  ssize n, q;
  consoleIn >> n >> q;

  std::unique_ptr<int[]> array(new int[n]);
  for (ssize i = 0; i < n; i++)
    consoleIn >> array[i];

  std::unique_ptr<i64[]> differenceArray(new i64[n + 1]);

  differenceArray[0] = array[0];
  for (ssize i = 1; i < n; i++)
    differenceArray[i] = array[i] - array[i - 1];
  differenceArray[n] = 0LL;

  auto ADD           = [&](const i64 &a, const i64 &b) { return a + b; };

  auto segmentTree   = SegmentTree<i64>(differenceArray, n + 1, 0LL, ADD);

  while (q-- > 0)
  {
    int choice, a, b, k, u;
    consoleIn >> choice;
    if (choice == 1)
    {
      consoleIn >> a >> b >> u;
      a--, b--;
      differenceArray[a] += u, differenceArray[b + 1] -= u;
      segmentTree.setAtIndex(a, differenceArray[a]);
      segmentTree.setAtIndex(b + 1, differenceArray[b + 1]);
    }
    else
    {
      consoleIn >> k;
      consoleOut << segmentTree.queryRange(0, k) << "\n";
    }
  }
}

} // namespace _RangeUpdateQueries

int main()
{
#ifdef ANTUMBRA
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
    consoleErr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};

  while (t-- > 0)
    _RangeUpdateQueries::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  consoleOut.flush();

  return 0;
}
