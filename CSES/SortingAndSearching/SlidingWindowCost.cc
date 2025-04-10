#include <algorithm> // IWYU pragma: keep
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <functional>
#include <memory>
#include <set>
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

namespace _SlidingWindowCost
{

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
};

struct MedianWindow
{
private:
  std::unique_ptr<int[]> array_;
  std::size_t current_begin_, current_end_;
  std::size_t size_, window_size_;

  std::size_t expected_low_size_, expected_high_size_;
  std::multiset<int> low_, high_;

  void balance_sets_()
  {
    while (low_.size() < expected_low_size_)
    {
      auto it = high_.begin();
      low_.insert(*it);
      high_.erase(it);
    }

    while (high_.size() < expected_high_size_)
    {
      auto it = --low_.end();
      high_.insert(*it);
      low_.erase(it);
    }
  }

public:
  MedianWindow(int array[], std::size_t array_size, std::size_t window_size)
      : array_(std::make_unique<int[]>(array_size)), current_begin_(0),
        current_end_(0), size_(array_size), window_size_(window_size)
  {

    if (window_size & 1)
      expected_low_size_  = (window_size >> 1) + 1,
      expected_high_size_ = window_size >> 1;
    else
      expected_low_size_ = expected_high_size_ = window_size >> 1;

    for (std::size_t i = 0; i < size_; i++)
      array_[i] = array[i];

    for (std::size_t i = 0; i < window_size_; i++)
      low_.insert(array_[i]);

    balance_sets_();
  }

  int next_median()
  {
    if (current_end_ == 0) [[unlikely]]
    {
      current_end_ = window_size_;
      return *low_.rbegin();
    }

    int r = array_[current_begin_++];

    if (low_.contains(r))
      low_.erase(low_.find(r));
    else
      high_.erase(high_.find(r));

    int e = array_[current_end_++];
    if (!high_.empty() && e > *high_.begin())
      high_.insert(e);
    else
      low_.insert(e);

    balance_sets_();
    return *low_.rbegin();
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
  template <std::size_t N>
  SegmentTree(const std::array<T, N> &array, T default_value,
              std::function<T(const T &, const T &)> function)
      : offset_(1LL << Algebra::ceil_log2(N)),
        tree_(std::make_unique<T[]>(offset_ << 1)), function_(function),
        defaultValue_(default_value)
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

  SegmentTree(T array[], std::size_t n, T default_value,
              std::function<T(const T &, const T &)> function)
      : offset_(1LL << Algebra::ceil_log2(n)),
        tree_(std::make_unique<T[]>(offset_ << 1)), function_(function),
        defaultValue_(default_value)
  {
    std::copy(array, array + n, &tree_[offset_]);

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

  void set_at_index(std::size_t index, T value)
  {
    index += offset_;
    tree_[index] = value;

    while (index != 1)
    {
      tree_[index >> 1] = function_(tree_[index], tree_[index ^ 1]);
      index >>= 1;
    }
  }

  T query_range(std::size_t from_idx, std::size_t past_end_idx)
  {
    from_idx += offset_, past_end_idx += offset_;

    T result{defaultValue_};
    while (from_idx < past_end_idx)
    {
      if (from_idx & 1)
        result = function_(result, tree_[from_idx++]);
      if (past_end_idx & 1)
        result = function_(result, tree_[--past_end_idx]);

      from_idx >>= 1, past_end_idx >>= 1;
    }

    return result;
  }
};

auto run() -> void
{
  int n, k;
  console_in >> n >> k;

  int input[n];
  int64_t difference_array[n + 1];
  for (int i = 0; i < n; i++)
    console_in >> input[i];

  difference_array[0] = input[0];
  for (int i = 1; i < n; i++)
    difference_array[i] = input[i] - input[i - 1];

  difference_array[n] = 0LL;

  auto SUM_SELECT = [](const int64_t &a, const int64_t &b) { return a + b; };
  SegmentTree segment_tree =
      SegmentTree<int64_t>(difference_array, n + 1, 0LL, SUM_SELECT);

  MedianWindow median_window(input, n, k);

  for (int i = 0; i < n - k + 1; i++)
  {
    int u = median_window.next_median();

    difference_array[i] += -u, difference_array[i + k] -= -u;
    segment_tree.set_at_index(i, static_cast<int>(difference_array[i]));
    segment_tree.set_at_index(i + k, static_cast<int>(difference_array[i + k]));

    console_out.append<"% ">(segment_tree.query_range(i, i + k));

    difference_array[i] += u, difference_array[i + k] -= u;
    segment_tree.set_at_index(i, static_cast<int>(difference_array[i]));
    segment_tree.set_at_index(i + k, static_cast<int>(difference_array[i + k]));
  }

  console_out << "\n";
}

} // namespace _SlidingWindowCost

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
    _SlidingWindowCost::run();

  console_out.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
