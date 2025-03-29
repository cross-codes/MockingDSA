#include <algorithm>
#include <array>
#include <bitset>
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
#include <utility>
#include <vector>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1 << 16
#endif

#define NO_AUTO_FLUSH 1

namespace IOfast
{
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

struct Ofast
{
  std::array<char, BUFFER_SIZE> buffer;
  size_t idx = 0;
  int const fd;

  [[nodiscard]] explicit Ofast(int const fd) noexcept : fd(fd)
  {
  }
  [[nodiscard]] explicit Ofast(char const f[]) noexcept
      : fd(open(f, O_WRONLY | O_CREAT, 0644))
  {
  }

  Ofast(Ofast const &)            = delete;
  Ofast &operator=(Ofast const &) = delete;

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

  Ofast &operator<<(char const c) noexcept
  {
    flush_if(1);
    buffer[idx++] = c;
    return *this;
  }

  template <class T, class = std::enable_if_t<std::is_integral<T>::value>,
            class unsT = typename std::make_unsigned<T>::type>
  Ofast &operator<<(T const a) noexcept
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

  Ofast &operator<<(char const s[]) noexcept
  {
    size_t len = strlen(s);
    flush_if(len);
    memcpy(&buffer[idx], s, len);
    idx += len;
    return *this;
  }

  Ofast &operator<<(std::string_view const s) noexcept
  {
    flush_if(s.size());
    memcpy(&buffer[idx], s.data(), s.size());
    idx += s.size();
    return *this;
  }

  Ofast &operator<<(std::string const &s) noexcept
  {
    flush_if(s.size());
    memcpy(&buffer[idx], s.data(), s.size());
    idx += s.size();
    return *this;
  }

  template <class T, class = std::enable_if_t<std::is_floating_point<T>::value>>
  Ofast &operator<<(T f) noexcept
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

  Ofast &operator<<(void *p) noexcept
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

struct Ifast
{
  std::array<char, BUFFER_SIZE> buffer;
  size_t idx = 0, size = 0;
  int const fd;

  [[nodiscard]] explicit Ifast(int const fd) noexcept : fd(fd)
  {
  }
  [[nodiscard]] explicit Ifast(char const f[]) noexcept : fd(open(f, O_RDONLY))
  {
  }
  Ifast(Ifast const &)            = delete;
  Ifast &operator=(Ifast const &) = delete;

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

  Ifast &operator>>(char &c) noexcept
  {
    flush();
    c = buffer[idx++];
    return *this;
  }

  template <class T, class = std::enable_if_t<std::is_integral<T>::value>>
  Ifast &operator>>(T &i) noexcept
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
} // namespace IOfast

IOfast::Ifast fastin(STDIN_FILENO);
IOfast::Ofast fastout(STDOUT_FILENO);
IOfast::Ofast fasterr(STDERR_FILENO);

namespace _E
{

struct FixedDensePrime
{
private:
  constexpr inline static int N = 20000000;
  std::array<int, N> minima_, powers_;
  std::bitset<N> parity_, squareFree_;

public:
  std::vector<int> primes;

  explicit FixedDensePrime() : minima_{}, powers_{}
  {
    for (int i = 2; i < (N + 1) >> 1; i++)
    {
      int minimum, power;
      if (minima_[i] == 0)
      {
        minimum = i;
        power   = 1;
        parity_.set(i, true);
        squareFree_.set(i, true);
        primes.push_back(i);
      }
      else
      {
        minimum = minima_[i];
        power   = powers_[i];
      }

      for (int e : primes)
      {
        int index{e * i};
        if (index < N)
        {
          minima_[index] = e;
          parity_.set(index, !parity_[i]);
          if (e == minimum)
          {
            powers_[index] = power + 1;
            break;
          }
          else
          {
            powers_[index] = 1;
            squareFree_.set(index, squareFree_[i]);
          }
        }
        else
          break;
      }
    }

    for (int i = (N + 1) >> 1 | 1; i < N; i += 2)
    {
      if (minima_[i] == 0)
      {
        parity_.set(i, true);
        squareFree_.set(i, true);
      }
    }
  }

  auto isSquareFree(int n) -> bool
  {
    return squareFree_[n];
  }

  auto getParity(int n) -> bool
  {
    return parity_[n];
  }

  auto totient(int n) -> int
  {
    int result{1};
    while (minima_[n] != 0)
    {
      int factor{1};
      for (int i = 1; i < powers_[n]; i++)
        factor *= minima_[n];
      result *= factor * (minima_[n] - 1);
      n /= factor * minima_[n];
    }

    if (n != 1)
      result *= n - 1;

    return result;
  }

  void forPrimeFactors(int n, std::function<void(const int &)> consume)
  {
    while (minima_[n] != 0)
    {
      consume(minima_[n]);
      int factor{1};
      for (int i = 0; i < powers_[n]; i++)
        factor *= minima_[n];
      n /= factor;
    }

    if (n != 1)
      consume(n);
  }

  void forPowers(int n, std::function<void(const int &)> consume)
  {
    while (minima_[n] != 0)
    {
      consume(powers_[n]);
      int factor{1};
      for (int i = 0; i < powers_[n]; i++)
        factor *= minima_[n];
      n /= factor;
    }

    if (n != 1)
      consume(1);
  }

  void forPrimeFactorsAndPowers(
      int n, std::function<void(const int &, const int &)> biConsume)
  {
    while (minima_[n] != 0)
    {
      biConsume(minima_[n], powers_[n]);
      int factor{1};
      for (int i = 0; i < powers_[n]; i++)
        factor *= minima_[n];
      n /= factor;
    }

    if (n != 1)
      biConsume(n, 1);
  }

  void forFactors(int n, bool include1, bool includeN,
                  std::function<void(const int &)> consume)
  {
    if (n == 1)
    {
      if (include1 && includeN)
        consume(1);
    }
    else
    {
      if (include1)
        consume(1);

      std::vector<int> primeFactors{}, powers{};

      forPrimeFactorsAndPowers(n, [&primeFactors, &powers](int a, int b) {
        primeFactors.push_back(a), powers.push_back(b);
      });

      std::vector<int> factors = primeFactors;
      std::unique_ptr<int[]> currentPowers(new int[factors.size()]);
      std::ranges::fill(currentPowers.get(),
                        currentPowers.get() + factors.size(), 1);

      int index{};
      while (true)
      {
        if (currentPowers[index] > powers[index])
          index++;
        else if (factors[index] == n)
        {
          if (includeN)
            consume(n);
          break;
        }
        else
        {
          consume(factors[index]);
          for (int i = 0; i <= index; i++)
            factors[i] = factors[index] * primeFactors[i];

          std::ranges::fill(currentPowers.get(), currentPowers.get() + index,
                            1);

          currentPowers[index]++;
          index = 0;
        }
      }
    }
  }
};

FixedDensePrime denseSieve;

auto run() -> void
{
  int n;
  fastin >> n;

  int64_t res{};
  for (const int &e : denseSieve.primes)
  {
    int64_t toAdd = n / e;
    if (toAdd == 0)
      break;
    res += toAdd;
  }

  fastout << res << "\n";
}

} // namespace _E

int main()
{
  int t{1};
  fastin >> t;

  while (t-- > 0)
    _E::run();

  fastout.flush();

  return 0;
}
