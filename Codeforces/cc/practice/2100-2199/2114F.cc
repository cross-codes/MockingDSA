#include <algorithm> // IWYU pragma: keep
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <string_view>
#include <type_traits>
#include <unistd.h>
#include <unordered_set>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

namespace io
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
    while (*this >> c, c > ' ')
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

InputReader cin(STDIN_FILENO);
OutputWriter cout(STDOUT_FILENO);
OutputWriter cerr(STDERR_FILENO);

} // namespace io

namespace _F
{

struct FixedDensePrime
{
private:
  constexpr inline static int N = 2000002;
  std::array<int, N> minima_, powers_;
  std::bitset<N> parity_, square_free_;

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
        square_free_.set(i, true);
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
            square_free_.set(index, square_free_[i]);
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
        square_free_.set(i, true);
      }
    }
  }

  auto is_square_free(int n) -> bool
  {
    return square_free_[n];
  }

  auto get_parity(int n) -> bool
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

  void for_prime_factors(int n, std::function<void(const int &)> consume)
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

  void for_powers(int n, std::function<void(const int &)> consume)
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

  void for_prime_factors_and_powers(
      int n, std::function<void(const int &, const int &)> bi_consume)
  {
    while (minima_[n] != 0)
    {
      bi_consume(minima_[n], powers_[n]);
      int factor{1};
      for (int i = 0; i < powers_[n]; i++)
        factor *= minima_[n];
      n /= factor;
    }

    if (n != 1)
      bi_consume(n, 1);
  }

  void for_factors(int n, bool include1, bool includeN,
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

      std::vector<int> prime_factors{}, powers{};

      for_prime_factors_and_powers(n, [&prime_factors, &powers](int a, int b) {
        prime_factors.push_back(a), powers.push_back(b);
      });

      std::vector<int> factors = prime_factors;
      std::unique_ptr<int[]> current_powers(new int[factors.size()]);
      std::ranges::fill(current_powers.get(),
                        current_powers.get() + factors.size(), 1);

      int index{};
      while (true)
      {
        if (current_powers[index] > powers[index])
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
            factors[i] = factors[index] * prime_factors[i];

          std::ranges::fill(current_powers.get(), current_powers.get() + index,
                            1);

          current_powers[index]++;
          index = 0;
        }
      }
    }
  }
};

FixedDensePrime dense_sieve{};

auto find_min_factors(int target, int upper_lim, int &num_factors) -> bool
{
  std::vector<int> factors{};
  dense_sieve.for_factors(target, true, true,
                          [&factors](int x) { factors.push_back(x); });

  std::sort(factors.begin(), factors.end());
  std::vector<int> divisors{};

  auto it = std::upper_bound(factors.begin(), factors.end(), upper_lim);
  if (it == factors.begin())
  {
    num_factors = INT_MAX;
    return false;
  }
  else
    std::copy(factors.begin(), it, std::back_inserter(divisors));

  std::queue<std::pair<int, int>> queue;
  std::unordered_set<int> visited;
  queue.emplace(target, 0);
  visited.insert(target);

  while (!queue.empty())
  {
    int current_factor = queue.front().first;
    int edges          = queue.front().second;
    queue.pop();

    if (current_factor == 1)
    {
      num_factors = edges;
      return true;
    }

    for (int d : divisors)
    {
      if (current_factor % d == 0)
      {
        int next_factor = current_factor / d;
        if (!visited.contains(next_factor))
        {
          visited.insert(next_factor);
          queue.emplace(next_factor, edges + 1);
        }
      }
    }
  }

  num_factors = INT_MAX;
  return false;

  // int nf{};
  // while (target != 1)
  // {
  //   std::vector<int> factors;
  //   dense_sieve.for_factors(target, false, true,
  //                           [&factors](int x) { factors.push_back(x); });
  //
  //   std::sort(factors.begin(), factors.end());
  //
  //   auto it = std::upper_bound(factors.begin(), factors.end(), upper_lim);
  //   if (it == factors.begin())
  //   {
  //     num_factors = INT_MAX;
  //     return false;
  //   }
  //
  //   nf += 1;
  //   int divide = *(--it);
  //   io::cout << "Dividing by: " << divide << "\n";
  //   target /= divide;
  // }
  //
  // num_factors = nf;
  // return true;
}

auto run() -> void
{
  int x, y, k;
  io::cin >> x >> y >> k;

  int gcd = std::__gcd(x, y);
  y /= gcd, x /= gcd;

  int n{}, m{};

  bool possible = find_min_factors(y, k, n);
  if (!possible)
  {
    io::cout << "-1\n";
    return;
  }

  possible = find_min_factors(x, k, m);
  if (!possible)
  {
    io::cout << "-1\n";
    return;
  }

  io::cout << m + n << "\n";
}

} // namespace _F

int main()
{
#ifdef ANTUMBRA
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
    io::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  io::cin >> t;

  while (t-- > 0)
    _F::run();

  io::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
