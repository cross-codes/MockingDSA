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

namespace IO
{

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1 << 20
#endif

#if (__cpp_nontype_template_parameter_class ||                                 \
     (__cpp_nontype_template_args >= 201411L))
template <std::size_t N> struct fixed_string
{
public:
  std::array<char, N> buf;

  constexpr fixed_string(char const s[]) noexcept
  {
    for (std::size_t i = 0; i < N; i++)
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

template <std::size_t N> fixed_string(char const (&)[N]) -> fixed_string<N - 1>;
#endif

struct OutputWriter
{
private:
  std::array<char, BUFFER_SIZE> buffer;
  std::size_t idx = 0;
  int const fd;

public:
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

  void flush_if_overflow(std::size_t x) noexcept
  {
#ifndef NO_AUTO_FLUSH
    if (buffer.size() - idx < x)
      flush();
#endif
  }

  OutputWriter &operator<<(char const c) noexcept
  {
    flush_if_overflow(1);
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
    std::uint8_t i = d.size();

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

    flush_if_overflow(d.size() - i);
    std::memcpy(&buffer[idx], &d[i], d.size() - i);
    idx += d.size() - i;
    return *this;
  }

  OutputWriter &operator<<(char const s[]) noexcept
  {
    size_t len = strlen(s);
    flush_if_overflow(len);
    std::memcpy(&buffer[idx], s, len);
    idx += len;
    return *this;
  }

  OutputWriter &operator<<(std::string_view const s) noexcept
  {
    flush_if_overflow(s.size());
    std::memcpy(&buffer[idx], s.data(), s.size());
    idx += s.size();
    return *this;
  }

  OutputWriter &operator<<(std::string const &s) noexcept
  {
    flush_if_overflow(s.size());
    std::memcpy(&buffer[idx], s.data(), s.size());
    idx += s.size();
    return *this;
  }

  template <class T, class = std::enable_if_t<std::is_floating_point<T>::value>>
  OutputWriter &operator<<(T f) noexcept
  {
    constexpr std::size_t precision = 6;

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
      flush_if_overflow(precision + 2);
      for (std::size_t i = 0; i < precision; i++)
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
      f *= std::pow(10, e);
      return *this << (unsigned)f << '.'
                   << (unsigned)(std::pow(10, precision - e - 1) *
                                 (f - (unsigned)f));
    }
  }

  OutputWriter &operator<<(void *p) noexcept
  {
    constexpr char const *digits = "0123456789abcdef";

    std::array<char, 2 * sizeof(void *) + 2> d;
    std::uint8_t i = d.size();

    static_assert(d.size() <= 256);
    static_assert(sizeof(size_t) == sizeof(void *));

    do
    {
      d[--i] = digits[(std::size_t)p & 0xF];
      p      = (void *)((std::size_t)p >> 4);
    } while (p);

    d[--i] = 'x';
    d[--i] = '0';

    flush_if_overflow(d.size() - i);
    std::memcpy(&buffer[idx], &d[i], d.size() - i);
    idx += d.size() - i;

    return *this;
  }

#if (__cpp_nontype_template_parameter_class ||                                 \
     (__cpp_nontype_template_args >= 201411L))
  template <fixed_string s, class... T> void append(T &&...v) noexcept
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
private:
  std::array<char, BUFFER_SIZE> buffer;
  std::size_t idx = 0, size = 0;
  int const fd;

public:
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

  InputReader &operator>>(std::string &x) noexcept
  {
    char c;
    while (*this >> c, c < ' ')
      continue;
    x = c;
    while (*this >> c, c >= ' ')
      x += c;

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
} // namespace IO

IO::InputReader console_in(STDIN_FILENO);
IO::OutputWriter console_out(STDOUT_FILENO);
IO::OutputWriter console_err(STDERR_FILENO);

namespace _1914C
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
      miller_rabin_base_sets_ = {
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

  constexpr inline static std::int64_t small_mul_mod(std::int64_t a,
                                                     std::int64_t b,
                                                     std::int64_t m)
  {
    return (a * b) % m;
  }

  constexpr inline static std::int64_t small_square_mod_(std::int64_t a,
                                                         std::int64_t m)
  {
    return (a * a) % m;
  }

  constexpr inline static std::int64_t small_pow_mod_(std::int64_t a,
                                                      std::int64_t p,
                                                      std::int64_t m)
  {
    std::int64_t res{1LL};
    for (; p != 0; p >>= 1)
    {
      if ((p & 1) != 0)
      {
        res = small_mul_mod(res, a, m);
      }
      a = small_square_mod_(a, m);
    }
    return res;
  }

  constexpr inline static std::int64_t large_plus_mod_(std::int64_t a,
                                                       std::int64_t b,
                                                       std::int64_t m)
  {
    return (a >= m - b) ? (a + b - m) : (a + b);
  }

  constexpr inline static std::int64_t large_times_2_to_the_32_mod_(
      std::int64_t a, std::int64_t m)
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

  constexpr inline static std::int64_t large_mul_mod_(std::int64_t a,
                                                      std::int64_t b,
                                                      std::int64_t m)
  {
    std::int64_t aHi{a >> 32};
    std::int64_t bHi{b >> 32};
    std::int64_t aLo{a & 0xFFFFFFFFLL};
    std::int64_t bLo{b & 0xFFFFFFFFLL};
    std::int64_t result{large_times_2_to_the_32_mod_(aHi * bHi, m)};
    result += aHi * bLo;
    if (result < 0)
    {
      result = remainder(result, m);
    }
    result += aLo * bHi;
    result = large_times_2_to_the_32_mod_(result, m);
    return large_plus_mod_(result, remainder(aLo * bLo, m), m);
  }

  constexpr inline static std::int64_t large_square_mod_(std::int64_t a,
                                                         std::int64_t m)
  {
    std::int64_t aHi{a >> 32};
    std::int64_t aLo{a & 0xFFFFFFFFLL};
    std::int64_t result{large_times_2_to_the_32_mod_(aHi * aHi, m)};
    std::int64_t hiLo{aHi * aLo * 2};
    if (hiLo < 0)
      hiLo = remainder(hiLo, m);
    result += hiLo;
    result = large_times_2_to_the_32_mod_(result, m);
    return large_plus_mod_(result, remainder(aLo * aLo, m), m);
  }

  constexpr inline static std::int64_t large_pow_mod_(std::int64_t a,
                                                      std::int64_t p,
                                                      std::int64_t m)
  {
    std::int64_t res{1LL};
    for (; p != 0; p >>= 1)
    {
      if (p & 1)
        res = large_mul_mod_(res, a, m);
      a = large_square_mod_(a, m);
    }

    return res;
  }

  inline static bool test_witness_small_(std::int64_t base, std::int64_t n)
  {
    int r{__builtin_ctzll(n - 1)};
    std::int64_t d{(n - 1) >> r};
    base %= n;
    if (base == 0)
      return true;

    std::int64_t a = small_pow_mod_(base, d, n);
    if (a == 1)
      return true;
    int j{};
    while (a != n - 1)
    {
      if (++j == r)
        return false;
      a = small_square_mod_(a, n);
    }

    return true;
  }

  inline static bool test_witness_large_(std::int64_t base, std::int64_t n)
  {
    int r{__builtin_ctzll(n - 1)};
    std::int64_t d{(n - 1) >> r};
    base %= n;
    if (base == 0)
      return true;

    std::int64_t a = large_pow_mod_(base, d, n);
    if (a == 1)
      return true;
    int j{};
    while (a != n - 1)
    {
      if (++j == r)
        return false;
      a = large_square_mod_(a, n);
    }

    return true;
  }

  constexpr inline static auto ex_GCD_(int a, int b, int &x, int &y) -> int
  {
    if (b == 0)
    {
      x = 1;
      y = 0;
      return a;
    }

    int x1, y1;
    int d = ex_GCD_(b, a % b, x1, y1);
    x     = y1;
    y     = x1 - y1 * (a / b);
    return d;
  }

public:
  constexpr inline static std::int64_t flip(std::int64_t a)
  {
    return a ^ INT64_MIN;
  }

  constexpr inline static int mul_mod(int a, int b, int m)
  {
    return static_cast<int>(small_mul_mod(a, b, m));
  }

  constexpr inline static int mod_pow(int n, int p, int m)
  {
    std::int64_t result{1LL};
    for (std::int64_t i = 1, j = n; i <= p; i <<= 1, j = j * j % m)
    {
      if (i & p)
        result = result * j % m;
    }

    return static_cast<int>(result);
  }

  constexpr inline static int coprime_mod_inv(int n, int m)
  {
    return mod_pow(n, m - 2, m);
  }

  inline static int log2(std::int64_t n)
  {
    return (n == 0) ? 0 : 63 - __builtin_clzll(n);
  }

  constexpr inline static int ceil_log2(std::int64_t n)
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

  static std::unique_ptr<double[]> solve_linear(double a, double b, double c,
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

  inline static std::unique_ptr<double[]> solve_quadratic(double a, double b,
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

    for (std::vector<std::int64_t> baseSet : miller_rabin_base_sets_)
    {
      if (n <= baseSet[0])
      {
        bool small = n <= FLOOR_SQRT_MAX_;
        if (small)
        {
          for (std::size_t i = 1; i < baseSet.size(); i++)
          {
            if (!test_witness_small_(baseSet[i], n))
              return false;
          }
        }
        else
        {
          for (std::size_t i = 1; i < baseSet.size(); i++)
          {
            if (!test_witness_large_(baseSet[i], n))
              return false;
          }
        }
      }

      return true;
    }

    throw new std::runtime_error("Assertion failed");
  }

  constexpr inline static std::uint64_t fibonnaci_number(
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

  constexpr inline static auto solve_diophantine(int a, int b, int c, int &x,
                                                 int &y, int &g) -> bool
  {
    g = ex_GCD_(std::abs(a), std::abs(b), x, y);
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

template <typename T> struct IdempotentSparseTable
{
private:
  std::function<T(const T &, const T &)> function_;
  std::vector<std::vector<T>> table;

public:
  IdempotentSparseTable(std::function<T(const T &, const T &)> func,
                        std::unique_ptr<T[]> &array, std::size_t n)
      : function_(func)
  {
    std::size_t K = Algebra::log2(n);

    table.resize(K + 1, std::vector<T>(n));
    std::copy(&array[0], &array[n], table[0].begin());

    for (std::size_t y = 1; y < table.size(); y++)
      for (std::size_t x = 0, k = 1 << (y - 1); x <= n - (1 << y); x++, k++)
        table[y][x] = function_(table[y - 1][x], table[y - 1][k]);
  }

  IdempotentSparseTable(std::function<T(const T &, const T &)> func, T array[],
                        std::size_t n)
      : function_(func)
  {
    std::size_t K = Algebra::log2(n);

    table.resize(K + 1, std::vector<T>(n));
    std::copy(array, array + n, table[0].begin());

    for (std::size_t y = 1; y < table.size(); y++)
      for (std::size_t x = 0, k = 1 << (y - 1); x <= n - (1 << y); x++, k++)
        table[y][x] = function_(table[y - 1][x], table[y - 1][k]);
  }

  T query_range(std::size_t fromIdx, std::size_t pastEndIdx)
  {
    std::size_t log2 = Algebra::log2(pastEndIdx - fromIdx);
    return function_(table[log2][fromIdx],
                     table[log2][pastEndIdx - (1 << log2)]);
  }
};

auto run() -> void
{
  int n, k;
  console_in >> n >> k;

  int a[n], b[n];
  int64_t prefix_a[n + 1];
  prefix_a[0] = 0;
  for (int i = 0; i < n; i++)
  {
    console_in >> a[i];
    prefix_a[i + 1] = prefix_a[i] + a[i];
  }
  for (int i = 0; i < n; i++)
    console_in >> b[i];

  auto MAX_SELECT   = [](const int &a, const int &b) { return std::max(a, b); };
  auto sparse_table = IdempotentSparseTable<int>(MAX_SELECT, b, n);

  int64_t max_score{INT64_MIN};
  for (int i = 1; i <= std::min(k, n); i++)
  {
    int b_max     = sparse_table.query_range(0, i);
    int64_t a_sum = prefix_a[i];
    max_score     = std::max(max_score, a_sum + (k - i) * b_max);
  }

  if (k > n)
  {
    max_score = std::max(
        max_score, prefix_a[n] + (k - n) * sparse_table.query_range(0, n));
  }

  console_out << max_score << "\n";
}

} // namespace _1914C

int main()
{
#ifdef ANTUMBRA
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
    console_err << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  console_in >> t;

  while (t-- > 0)
    _1914C::run();

  console_out.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
