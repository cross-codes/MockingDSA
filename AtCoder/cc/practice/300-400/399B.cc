#include <algorithm> // IWYU pragma: keep
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <memory>
#include <random>
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

namespace _399B
{

struct Random
{
private:
  std::random_device random_device_;
  std::mt19937_64 engine_;

  Random() : engine_(random_device_())
  {
  }
  Random(const Random &)            = delete;
  Random &operator=(const Random &) = delete;

public:
  static Random &get_instance()
  {
    static Random instance;
    return instance;
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_uniform_integer(T p, T r)
  {
    std::uniform_int_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_uniform_real(T p, T r)
  {
    std::uniform_real_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_normal_real(T p, T r)
  {
    std::normal_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  inline bool next_bernoulli()
  {
    std::bernoulli_distribution distribution;
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_binomial_real(T p, T r)
  {
    std::binomial_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_poisson_real(T p, T r)
  {
    std::poisson_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_exponential_real(T p, T r)
  {
    std::exponential_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_gamma_real(T p, T r)
  {
    std::gamma_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_weibull_real(T p, T r)
  {
    std::weibull_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_log_normal_real(T p, T r)
  {
    std::lognormal_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_chi_squared_real(T p, T r)
  {
    std::chi_squared_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_cauchy_real(T p, T r)
  {
    std::cauchy_distribution<T> distribution(p, r);
    return distribution(engine_);
  }

  template <typename T>
    requires std::integral<T> || std::floating_point<T>
  inline T next_t_real(T p, T r)
  {
    std::student_t_distribution<T> distribution(p, r);
    return distribution(engine_);
  }
};

struct Array
{
  /*
   * TODO: Make implementations for std::array
   */

private:
  Array();
  inline static Random &random_ = Random::get_instance();

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto index_partition_(std::unique_ptr<T[]> &A, std::ptrdiff_t p,
                                      std::ptrdiff_t r) -> std::ptrdiff_t
  {
    T x              = A[r];
    std::ptrdiff_t i = p - 1;

    for (std::ptrdiff_t j = p; j <= r - 1; j++)
    {
      if (A[j] <= x)
      {
        i++;
        std::swap(A[i], A[j]);
      }
    }

    std::swap(A[i + 1], A[r]);
    return i + 1;
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto index_partition_(std::vector<T> &A, std::ptrdiff_t p,
                                      std::ptrdiff_t r) -> std::ptrdiff_t
  {
    T x              = A[r];
    std::ptrdiff_t i = p - 1;

    for (std::ptrdiff_t j = p; j <= r - 1; j++)
    {
      if (A[j] <= x)
      {
        i++;
        std::swap(A[i], A[j]);
      }
    }

    std::swap(A[i + 1], A[r]);
    return i + 1;
  }

  template <typename T>
    requires std::three_way_comparable<T>
  static auto randomized_partition_(std::unique_ptr<T[]> &A, std::ptrdiff_t p,
                                    std::ptrdiff_t r) -> std::ptrdiff_t
  {
    std::ptrdiff_t i =
        static_cast<std::ptrdiff_t>(random_.next_uniform_integer<int>(
            static_cast<int>(p), static_cast<int>(r)));
    std::swap(A[i], A[r]);

    return index_partition_(A, p, r);
  }

  template <typename T>
    requires std::three_way_comparable<T>
  static auto randomized_parition_(std::vector<T> &A, std::ptrdiff_t p,
                                   std::ptrdiff_t r) -> std::ptrdiff_t
  {
    std::ptrdiff_t i =
        static_cast<std::ptrdiff_t>(random_.next_uniform_integer<int>(
            static_cast<int>(p), static_cast<int>(r)));
    std::swap(A[i], A[r]);

    T pivot = A[r];
    auto it = std::partition(&A[p], &A[r],
                             [pivot](const T &val) { return val <= pivot; });

    std::iter_swap(it, &A[r]);
    return std::distance(&A[p], it);
  }

  template <typename T>
  inline static auto lomuto_partition_(std::unique_ptr<T[]> &nums,
                                       std::ptrdiff_t p, std::ptrdiff_t r)
      -> std::ptrdiff_t
  {
    std::ptrdiff_t mid = (p + r) >> 1;
    std::swap(nums[mid], nums[p + 1]);

    if (nums[p] < nums[r])
      std::swap(nums[p], nums[r]);
    if (nums[p + 1] < nums[r])
      std::swap(nums[p + 1], nums[r]);
    if (nums[p] < nums[p + 1])
      std::swap(nums[p], nums[p + 1]);

    T pivot          = nums[p + 1];
    std::ptrdiff_t i = p + 1, j = r;

    while (true)
    {
      while (nums[++i] > pivot)
        continue;
      while (nums[--j] < pivot)
        continue;
      if (i > j)
        break;
      std::swap(nums[i], nums[j]);
    }

    nums[p + 1] = nums[j];
    nums[j]     = pivot;
    return j;
  }

  template <typename T>
  inline static auto lomuto_partition_(std::vector<T> &nums, std::ptrdiff_t p,
                                       std::ptrdiff_t r) -> std::ptrdiff_t
  {
    std::ptrdiff_t mid = (p + r) >> 1;
    std::swap(nums[mid], nums[p + 1]);

    if (nums[p] < nums[r])
      std::swap(nums[p], nums[r]);
    if (nums[p + 1] < nums[r])
      std::swap(nums[p + 1], nums[r]);
    if (nums[p] < nums[p + 1])
      std::swap(nums[p], nums[p + 1]);

    T pivot          = nums[p + 1];
    std::ptrdiff_t i = p + 1, j = r;

    while (true)
    {
      while (nums[++i] > pivot)
        continue;
      while (nums[--j] < pivot)
        continue;
      if (i > j)
        break;
      std::swap(nums[i], nums[j]);
    }

    nums[p + 1] = nums[j];
    nums[j]     = pivot;
    return j;
  }

public:
  inline static void integer_bucket_sort(std::unique_ptr<int[]> &array,
                                         std::size_t length)
  {
    int bits  = 4;
    int radix = 1 << bits;
    std::vector<std::vector<int>> buckets(radix, std::vector<int>(length));

    std::vector<int> size(radix);
    for (std::size_t i = 0; i < length; i++)
    {
      int e                         = array[i];
      int index                     = e & (radix - 1);
      buckets[index][size[index]++] = e;
    }

    std::vector<std::vector<int>> new_buckets(radix, std::vector<int>(length));
    for (unsigned int i = bits; i < sizeof(int) * 8; i += bits)
    {
      std::vector<int> new_size(radix);
      for (int j = 0; j < radix; j++)
      {
        for (int k = 0; k < size[j]; k++)
        {
          int index =
              (static_cast<unsigned int>(buckets[j][k]) >> i) & (radix - 1);
          new_buckets[index][new_size[index]++] = buckets[j][k];
        }
      }
      std::swap(buckets, new_buckets);
      size = new_size;
    }

    {
      int i = 0;
      for (int j = radix >> 1; j < radix; j++)
      {
        for (int k = 0; k < size[j]; k++)
          array[i++] = buckets[j][k];
      }
      for (int j = 0; j < radix >> 1; j++)
      {
        for (int k = 0; k < size[j]; k++)
          array[i++] = buckets[j][k];
      }
    }
  }

  inline static void integer_bucket_sort(std::vector<int> &vector)
  {
    int bits  = 4;
    int radix = 1 << bits;
    std::vector<std::vector<int>> buckets(radix,
                                          std::vector<int>(vector.size()));

    std::vector<int> size(radix);
    for (int e : vector)
    {
      int index                     = e & (radix - 1);
      buckets[index][size[index]++] = e;
    }

    std::vector<std::vector<int>> new_buckets(radix,
                                              std::vector<int>(vector.size()));
    for (unsigned int i = bits; i < sizeof(int) * 8; i += bits)
    {
      std::vector<int> new_size(radix);
      for (int j = 0; j < radix; j++)
      {
        for (int k = 0; k < size[j]; k++)
        {
          int index =
              (static_cast<unsigned int>(buckets[j][k]) >> i) & (radix - 1);
          new_buckets[index][new_size[index]++] = buckets[j][k];
        }
      }
      std::swap(buckets, new_buckets);
      size = new_size;
    }

    {
      int i = 0;
      for (int j = radix >> 1; j < radix; j++)
      {
        for (int k = 0; k < size[j]; k++)
          vector[i++] = buckets[j][k];
      }
      for (int j = 0; j < radix >> 1; j++)
      {
        for (int k = 0; k < size[j]; k++)
          vector[i++] = buckets[j][k];
      }
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  static void randomized_quick_sort(std::unique_ptr<T[]> &A,
                                    std::ptrdiff_t start,
                                    std::ptrdiff_t pastEnd)
  {
    while (start < pastEnd - 1)
    {
      std::ptrdiff_t q = randomized_partition_(A, start, pastEnd - 1);
      randomized_quick_sort(A, start, q);
      start = q + 1;
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  static void randomized_quick_sort(std::vector<T> &A, std::ptrdiff_t start,
                                    std::ptrdiff_t pastEnd)
  {
    while (start < pastEnd - 1)
    {
      std::ptrdiff_t q = randomized_partition_(A, start, pastEnd - 1);
      randomized_quick_sort(A, start, q);
      start = q + 1;
    }
  }

  inline static auto stable_counting_sort(std::unique_ptr<std::uint32_t[]> &A,
                                          std::size_t n, std::uint32_t max)
      -> std::unique_ptr<std::uint32_t[]>
  {
    std::unique_ptr<std::uint32_t[]> B(new std::uint32_t[n]),
        C(new std::uint32_t[max + 1]);
    std::memset(C.get(), 0x00, sizeof(int) * (max + 1));

    for (std::uint32_t j = 0; j < n; j++)
      C[A[j]]++;

    for (std::uint32_t i = 1; i <= max; i++)
      C[i] = C[i] + C[i - 1];

    for (std::ptrdiff_t j = n - 1; j >= 0; j--)
    {
      B[C[A[j]] - 1] = A[j];
      C[A[j]]--;
    }

    return B;
  }

  inline static auto stable_counting_sort(std::vector<std::uint32_t> &A,
                                          std::size_t n, std::uint32_t max)
      -> std::vector<std::uint32_t>
  {
    std::vector<std::uint32_t> B(n), C(max + 1, 0);

    for (std::uint32_t j = 0; j < n; j++)
      C[A[j]]++;

    for (std::uint32_t i = 1; i <= max; i++)
      C[i] = C[i] + C[i - 1];

    for (std::ptrdiff_t j = n - 1; j >= 0; j--)
    {
      B[C[A[j]] - 1] = A[j];
      C[A[j]]--;
    }

    return B;
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto index_binary_search(const std::unique_ptr<T[]> &a,
                                         std::ptrdiff_t start,
                                         std::ptrdiff_t pastEnd, const T &key)
      -> std::ptrdiff_t
  {
    std::ptrdiff_t i = start, j = pastEnd - 1;
    while (i <= j)
    {
      std::ptrdiff_t m = (i + j) >> 1;
      if (a[m] < key)
        i = m + 1;
      else if (a[m] > key)
        j = m - 1;
      else
        return m;
    }

    return -(i + 1);
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto index_binary_search(const std::vector<T> &a,
                                         std::ptrdiff_t start,
                                         std::ptrdiff_t pastEnd, const T &key)
      -> std::ptrdiff_t
  {
    std::ptrdiff_t i = start, j = pastEnd - 1;
    while (i <= j)
    {
      std::ptrdiff_t m = (i + j) >> 1;
      if (a[m] < key)
        i = m + 1;
      else if (a[m] > key)
        j = m - 1;
      else
        return m;
    }

    return -(i + 1);
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto index_ternary_search(const std::unique_ptr<T[]> &a,
                                          std::ptrdiff_t start,
                                          std::ptrdiff_t pastEnd, const T &key)
      -> std::ptrdiff_t
  {
    std::ptrdiff_t i = start, j = pastEnd - 1;
    while (i < j - 1)
    {
      std::ptrdiff_t l = (i + j) / 3;
      std::ptrdiff_t u = ((i + j) / 3) << 1;

      if (key > a[u])
      {
        i = u + 1;
      }
      else if (key > a[l])
      {
        i = l + 1;
        j = u;
      }
      else
      {
        j = l;
      }
    }

    if (key == a[i])
      return i;
    else if (key == a[j])
      return j;
    else
      return -1;
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto index_ternary_search(const std::vector<T> &a,
                                          std::ptrdiff_t start,
                                          std::ptrdiff_t pastEnd, const T &key)
      -> std::ptrdiff_t
  {
    std::ptrdiff_t i = start, j = pastEnd - 1;
    while (i < j - 1)
    {
      std::ptrdiff_t l = (i + j) / 3;
      std::ptrdiff_t u = ((i + j) / 3) << 1;

      if (key > a[u])
      {
        i = u + 1;
      }
      else if (key > a[l])
      {
        i = l + 1;
        j = u;
      }
      else
      {
        j = l;
      }
    }

    if (key == a[i])
      return i;
    else if (key == a[j])
      return j;
    else
      return -1;
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto inverse_order_statistic(std::unique_ptr<T[]> &A,
                                             std::ptrdiff_t start,
                                             std::ptrdiff_t pastEnd,
                                             std::size_t order) -> T
  {
    std::ptrdiff_t left = start, right = pastEnd - 1;

    while (true)
    {
      if (right <= left + 1)
      {
        if (right == left + 1 && A[right] > A[left])
          std::swap(A[left], A[right]);
        return A[order - 1];
      }

      std::size_t j = lomuto_partition_(A, left, right);

      if (j >= order - 1)
        right = j - 1;
      if (j <= order - 1)
        left = j + 1;
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto inverse_order_statistic(std::vector<T> &A,
                                             std::ptrdiff_t start,
                                             std::ptrdiff_t pastEnd,
                                             std::size_t order) -> T
  {
    std::ptrdiff_t left = start, right = pastEnd - 1;

    while (true)
    {
      if (right <= left + 1)
      {
        if (right == left + 1 && A[right] > A[left])
          std::swap(A[left], A[right]);
        return A[order - 1];
      }

      std::size_t j = lomuto_partition_(A, left, right);

      if (j >= order - 1)
        right = j - 1;
      if (j <= order - 1)
        left = j + 1;
    }
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto order_statistic(std::unique_ptr<T[]> &A,
                                     std::ptrdiff_t start,
                                     std::ptrdiff_t pastEnd, std::size_t order)
      -> T
  {
    return inverse_order_statistic(A, start, pastEnd,
                                   pastEnd - start - order + 1);
  }

  template <typename T>
    requires std::three_way_comparable<T>
  inline static auto order_statistic(std::vector<T> &A, std::ptrdiff_t start,
                                     std::ptrdiff_t pastEnd, std::size_t order)
      -> T
  {
    return inverse_order_statistic(A, start, pastEnd,
                                   pastEnd - start - order + 1);
  }
};

auto determine(const std::unique_ptr<bool[]> &determined,
               const std::unique_ptr<int[]> &rank,
               const std::unique_ptr<int[]> &scores, int r, int max, int n)
    -> int
{
  int updated{};
  for (int i = 0; i < n; i++)
  {
    if (determined[i])
      continue;

    if (scores[i] == max)
    {
      rank[i]       = r;
      determined[i] = true;
      updated++;
    }
  }

  return updated;
}

auto run() -> void
{
  int n;
  console_in >> n;

  std::unique_ptr<int[]> scores(new int[n]), scores_copy(new int[n]),
      rank(new int[n]);
  std::unique_ptr<bool[]> determined(new bool[n]);

  std::fill(determined.get(), determined.get() + n, false);

  for (int i = 0; i < n; i++)
  {
    console_in >> scores[i];
    scores_copy[i] = scores[i];
  }

  int updated{}, os{1}, r{1};
  while (updated != n)
  {
    int max = Array::inverse_order_statistic(scores_copy, 0, n, os);
    int k   = determine(determined, rank, scores, r, max, n);
    updated += k;
    r += k;
    os += k;
  }

  for (int i = 0; i < n; i++)
    console_out << rank[i] << "\n";
}

} // namespace _399B

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
    _399B::run();

  console_out.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
