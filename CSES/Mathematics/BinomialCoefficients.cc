#include <algorithm> // IWYU pragma: keep
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
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

namespace _BinomialCoefficients
{

struct MontRep
{
public:
  std::uint64_t value;

  explicit constexpr MontRep() : value(0)
  {
  }

private:
  explicit constexpr MontRep(std::uint64_t v) : value(v)
  {
  }

  friend struct Montgomery;
};

struct Montgomery
{
public:
  std::uint32_t MOD, MODR;
  constexpr explicit Montgomery(std::uint32_t n) : MOD(n), MODR(1)
  {
    for (int i = 0; i < 5; i++)
      MODR *= 2 - n * MODR;
  }

  auto reduce(std::uint64_t x) const noexcept -> std::uint32_t
  {
    std::uint32_t q = static_cast<std::uint32_t>(x) * MODR;
    std::uint64_t m = static_cast<std::uint64_t>(q) * MOD;
    std::uint32_t y = (x - m) >> 32;
    return x < m ? y + MOD : y;
  }

  auto reduce(MontRep x) const noexcept -> std::uint32_t
  {
    return reduce(x.value);
  }

  auto multiply(MontRep x, MontRep y) const noexcept -> MontRep
  {
    return MontRep(reduce(static_cast<std::uint64_t>(x.value) * y.value));
  }

  auto transform(std::uint64_t x) const noexcept -> MontRep
  {
    return MontRep((x << 32) % MOD);
  }

  auto add(MontRep x, MontRep y) const noexcept -> MontRep
  {
    auto res = x.value + y.value;
    if (res >= MOD)
      res -= MOD;
    return MontRep(res);
  }

  auto mod_pow(MontRep base, std::uint64_t power) const noexcept -> MontRep
  {
    MontRep result = transform(1ULL);
    MontRep j      = base;
    for (std::uint64_t i = 1; i <= power; i <<= 1, j = multiply(j, j))
      if (i & power)
        result = multiply(result, j);

    return result;
  }

  auto mod_pow(std::uint64_t base, std::uint64_t power) const noexcept
      -> MontRep
  {
    return mod_pow(transform(base), power);
  }

  auto coprime_mod_inv(MontRep n) const noexcept -> MontRep
  {
    return mod_pow(n, MOD - 2);
  }
};

constexpr int N        = 1000000;
constexpr uint64_t MOD = static_cast<uint64_t>(1e9 + 7);
std::array<MontRep, N + 1> factorials, inverseFactorials;

constexpr Montgomery space(MOD);

auto run() -> void
{
  factorials[0] = space.transform(1);
  for (int i = 1; i <= N; i++)
    factorials[i] = space.multiply(factorials[i - 1], space.transform(i));

  for (int i = 0; i <= N; i++)
    inverseFactorials[i] = space.coprime_mod_inv(factorials[i]);

  uint32_t n;
  console_in >> n;

  while (n-- > 0)
  {
    uint32_t a, b;
    console_in >> a >> b;

    auto res = space.multiply(factorials[a], inverseFactorials[b]);
    res      = space.multiply(res, inverseFactorials[a - b]);

    console_out << space.reduce(res) << "\n";
  }
}

} // namespace _BinomialCoefficients

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

  while (t-- > 0)
    _BinomialCoefficients::run();

  console_out.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
