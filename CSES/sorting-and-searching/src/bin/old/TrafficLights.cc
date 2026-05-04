#include <algorithm> // IWYU pragma: keep
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <unistd.h>
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

namespace _TrafficLights
{

struct Interval
{
  int start, end;
  Interval(int s, int e) : start(s), end(e) {};
};

struct IntervalNode
{
  Interval interval;
  int max_end, max_size, incl_height;

  std::unique_ptr<IntervalNode> left;
  std::unique_ptr<IntervalNode> right;

  IntervalNode(const Interval &i)
      : interval(i), max_end(i.end), max_size(i.end - i.start + 1),
        incl_height(1) {};
};

struct DisjointIntervalAVLTree
{
  std::unique_ptr<IntervalNode> root;

  int incl_height(const std::unique_ptr<IntervalNode> &node) const
  {
    return node ? node->incl_height : 0;
  }

  void update(IntervalNode *node)
  {
    node->incl_height =
        1 + std::max(incl_height(node->left), incl_height(node->right));
    node->max_end  = node->interval.end;
    node->max_size = node->interval.end - node->interval.start + 1;

    if (node->left)
    {
      node->max_end  = std::max(node->max_end, node->left->max_end);
      node->max_size = std::max(node->max_size, node->left->max_size);
    }
    if (node->right)
    {
      node->max_end  = std::max(node->max_end, node->right->max_end);
      node->max_size = std::max(node->max_size, node->right->max_size);
    }
  }

  std::unique_ptr<IntervalNode> rotate_right(std::unique_ptr<IntervalNode> y)
  {
    auto x   = std::move(y->left);
    y->left  = std::move(x->right);
    x->right = std::move(y);
    update(x->right.get());
    update(x.get());
    return x;
  }

  std::unique_ptr<IntervalNode> rotate_left(std::unique_ptr<IntervalNode> x)
  {
    auto y   = std::move(x->right);
    x->right = std::move(y->left);
    y->left  = std::move(x);
    update(y->left.get());
    update(y.get());
    return y;
  }

  std::unique_ptr<IntervalNode> insert(std::unique_ptr<IntervalNode> node,
                                       const Interval &interval)
  {
    if (!node)
      return std::make_unique<IntervalNode>(interval);

    if (interval.start < node->interval.start)
      node->left = insert(std::move(node->left), interval);
    else
      node->right = insert(std::move(node->right), interval);

    update(node.get());
    int balance = incl_height(node->left) - incl_height(node->right);

    if (balance > 1)
    {
      if (interval.start >= node->left->interval.start)
        node->left = rotate_left(std::move(node->left));
      return rotate_right(std::move(node));
    }
    if (balance < -1)
    {
      if (interval.start < node->right->interval.start)
        node->right = rotate_right(std::move(node->right));
      return rotate_left(std::move(node));
    }
    return node;
  }

  std::unique_ptr<IntervalNode> delete_node(std::unique_ptr<IntervalNode> node,
                                            const Interval &target)
  {
    if (!node)
      return nullptr;

    if (target.start < node->interval.start)
      node->left = delete_node(std::move(node->left), target);
    else if (target.start > node->interval.start)
      node->right = delete_node(std::move(node->right), target);
    else
    {
      if (node->interval.end != target.end)
        node->right = delete_node(std::move(node->right), target);
      else
      {
        if (!node->left)
          return std::move(node->right);
        else if (!node->right)
          return std::move(node->left);
        else
        {
          IntervalNode *minNode = min_value_node(node->right.get());
          node->interval        = minNode->interval;
          node->right = delete_node(std::move(node->right), minNode->interval);
        }
      }
    }

    update(node.get());
    int balance = incl_height(node->left) - incl_height(node->right);

    if (balance > 1)
    {
      if (incl_height(node->left->left) >= incl_height(node->left->right))
        return rotate_right(std::move(node));
      else
      {
        node->left = rotate_left(std::move(node->left));
        return rotate_right(std::move(node));
      }
    }
    if (balance < -1)
    {
      if (incl_height(node->right->right) >= incl_height(node->right->left))
        return rotate_left(std::move(node));
      else
      {
        node->right = rotate_right(std::move(node->right));
        return rotate_left(std::move(node));
      }
    }
    return node;
  }

  IntervalNode *min_value_node(IntervalNode *node) const
  {
    while (node && node->left)
      node = node->left.get();
    return node;
  }

public:
  DisjointIntervalAVLTree()                                           = default;
  DisjointIntervalAVLTree(const DisjointIntervalAVLTree &)            = delete;
  DisjointIntervalAVLTree &operator=(const DisjointIntervalAVLTree &) = delete;

  void insert(int start, int end)
  {
    root = insert(std::move(root), Interval(start, end));
  }

  void remove(int start, int end)
  {
    root = delete_node(std::move(root), Interval(start, end));
  }

  Interval *interval_containing(int p) const
  {
    IntervalNode *current = root.get();
    while (current)
    {
      if (p >= current->interval.start && p <= current->interval.end)
        return &current->interval;
      if (current->left && p <= current->left->max_end)
        current = current->left.get();
      else
        current = current->right.get();
    }
    return nullptr;
  }

  Interval *largest_interval() const
  {
    IntervalNode *current = root.get();
    while (current)
    {
      if (current->left && current->left->max_size == current->max_size)
        current = current->left.get();
      else if (current->right && current->right->max_size == current->max_size)
        current = current->right.get();
      else
        return &current->interval;
    }
    return nullptr;
  }

  int largest_interval_size() const
  {
    return root->max_size;
  }
};

auto run() -> void
{
  int x, n;
  io::cin >> x >> n;

  DisjointIntervalAVLTree interval_tree;
  interval_tree.insert(1, x);

  for (int i = 0; i < n; i++)
  {
    int p;
    io::cin >> p;

    auto to_split = interval_tree.interval_containing(p);
    int start{to_split->start}, end{to_split->end};

    interval_tree.remove(start, end);

    if (start <= p)
      interval_tree.insert(start, p);
    if (end >= p + 1)
      interval_tree.insert(p + 1, end);

    io::cout << interval_tree.largest_interval_size() << " ";
  }
}

} // namespace _TrafficLights

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

  while (t-- > 0)
    _TrafficLights::run();

  io::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
