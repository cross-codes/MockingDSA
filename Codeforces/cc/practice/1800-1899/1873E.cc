#include <algorithm> // IWYU pragma: keep
#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <numeric>
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

  InputReader &operator>>(char &c) noexcept
  {
    flush();
    c = buffer[idx++];
    return *this;
  }

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

namespace _1873E
{

template <typename T>
concept Predicate = requires(T t, int64_t x) {
  { t(x) } -> std::convertible_to<bool>;
};

struct Algebra
{
private:
  Algebra();
  constexpr inline static double EPSILON_{1E-6};

  constexpr inline static std::uint64_t MOD{
      static_cast<std::uint64_t>(1e9 + 7)};

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
  constexpr inline static auto flip(std::int64_t a) -> std::int64_t
  {
    return a ^ INT64_MIN;
  }

  constexpr inline static auto mod_pow(int n, int p, int m) -> int
  {
    std::int64_t result{1LL};
    for (std::int64_t i = 1, j = n; i <= p; i <<= 1, j = j * j % m)
      if (i & p)
        result = result * j % m;

    return static_cast<int>(result);
  }

  constexpr inline static auto coprime_mod_inv(int n, int m) -> int
  {
    return mod_pow(n, m - 2, m);
  }

  inline static auto log2(std::int64_t n) -> std::int64_t
  {
    return std::__lg(n);
  }

  constexpr inline static auto ceil_log2(std::int64_t n) -> std::int64_t
  {
    return (n == 1) ? 1 : 64 - __builtin_clzll(n - 1);
  }

  constexpr inline static auto is_prime(int64_t n) -> bool
  {
    if (n < 2)
      return false;

    int64_t x{2LL};
    while (x * x <= n)
    {
      if (n % x == 0)
        return false;
      x++;
    }

    return true;
  }

  constexpr inline static auto equal(double a, double b) -> bool
  {
    return std::abs(a - b) < EPSILON_;
  }

  constexpr inline static auto equal0(double a) -> bool
  {
    return std::abs(a) < EPSILON_;
  }

  inline static double *solve_linear(double a, double b, double c, double d,
                                     double e, double f)
  {
    double D{a * e - b * d};
    double Dx{c * e - b * f};
    double Dy{a * f - c * d};

    if (equal0(D))
    {
      std::size_t size = equal0(Dx) && equal0(Dy) ? 1 : 0;
      double *result   = new double[size];
      std::memset(result, 0x00, sizeof(int) * size);
      return result;
    }
    else
    {
      double *result = new double[2];
      result[0] = Dx / D, result[1] = Dy / D;
      return result;
    }
  }

  inline static double *solve_quadratic(double a, double b, double c)
  {
    double delta{b * b - 4 * a * c};
    if (equal0(delta))
    {
      double *result = new double[1];
      result[0]      = -b / (a * 2);
      return result;
    }
    else if (delta < 0)
    {
      double *result = new double[1];
      result[0]      = 0;
      return 0;
    }
    else
    {
      double a2{a * 2};
      double x{(-b / a2)};
      double y{std::sqrt(delta) / a2};

      double *result = new double[2];
      result[0] = x + y, result[1] = x - y;

      return result;
    }
  }

  constexpr inline static auto fibonnaci_number(std::uint64_t n,
                                                std::uint64_t modulus = MOD)
      -> std::uint64_t
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

  constexpr inline static void binary_search(Predicate auto pred,
                                             int64_t &lower_bound,
                                             int64_t &upper_bound)
  {
    assert(lower_bound < upper_bound);
    int64_t &L{lower_bound}, &R{upper_bound};
    while (R - L > 1)
    {
      int64_t M         = std::midpoint(L, R);
      (pred(M) ? R : L) = M;
    }
  }
};

auto run() -> void
{
  int n, x;
  console_in >> n >> x;

  int64_t a[n], min_height{INT_MAX}, max_height{INT_MIN};
  for (int i = 0; i < n; i++)
  {
    console_in >> a[i];
    min_height = std::min(min_height, a[i]);
    max_height = std::max(max_height, a[i]);
  }

  auto predicate = [&a, &n, &x](int64_t m) {
    int64_t water{};
    for (int i = 0; i < n; i++)
      water += std::max(m - a[i], static_cast<int64_t>(0));

    return water > x;
  };

  int64_t L{min_height - 1}, R{x + max_height + 1};
  Algebra::binary_search(predicate, L, R);

  console_out << L << "\n";
}

} // namespace _1873E

int main()
{
  int t{1};
  console_in >> t;

  while (t-- > 0)
    _1873E::run();

  console_out.flush();

  return 0;
}
