#include <algorithm> // IWYU pragma: keep
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <queue>
#include <set>
#include <stack>
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

template <> struct std::hash<std::tuple<int, int, int>>
{
  std::size_t operator()(const std::tuple<int, int, int> &t) const noexcept
  {
    std::size_t h1 = std::hash<int>{}(std::get<0>(t));
    std::size_t h2 = std::hash<int>{}(std::get<1>(t));
    std::size_t h3 = std::hash<int>{}(std::get<2>(t));

    return (h1 << 2) ^ (h2 << 1) ^ h3;
  }
};

namespace _59E
{

struct State
{
  int p, id, d;

  State(int p, int c, int d) : p(p), id(c), d(d) {};
};

constexpr int INF = static_cast<int>(1e9);

auto run() -> void
{
  int n, m, k;
  io::cin >> n >> m >> k;

  std::vector<int> adj[n];
  for (int i = 0; i < m; i++)
  {
    int x, y;
    io::cin >> x >> y;

    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  std::set<std::tuple<int, int, int>> forbidden{};
  for (int i = 0; i < k; i++)
  {
    int u, v, w;
    io::cin >> u >> v >> w;
    forbidden.insert(std::make_tuple(u - 1, v - 1, w - 1));
  }

  int dist[n][n];
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      dist[i][j] = INF;

  auto cmp = [](const State &a, const State &b) -> bool { return a.d > b.d; };

  std::priority_queue<State, std::vector<State>, decltype(cmp)> queue{};

  for (const int &v : adj[0])
  {
    dist[0][v] = 1;
    queue.emplace(0, v, 1);
  }

  while (!queue.empty())
  {
    State state = queue.top();
    queue.pop();
    int p{state.p}, u{state.id}, d{state.d};
    if (dist[p][u] < d)
      continue;

    for (const int &v : adj[u])
    {
      if (forbidden.contains(std::make_tuple(p, u, v)))
        continue;

      if (dist[u][v] > d + 1)
      {
        dist[u][v] = d + 1;
        queue.emplace(u, v, d + 1);
      }
    }
  }

  int min_dist{INF};
  for (int i = 0; i < n; i++)
    min_dist = std::min(min_dist, dist[i][n - 1]);

  if (min_dist == INF)
  {
    io::cout << "-1\n";
    return;
  }

  std::stack<int> stack{};
  int curr{n - 1}, prev{-INF};
  while (curr > 0)
  {
    stack.push(curr);
    int best_parent{-1};
    for (int i = 0; i < n; i++)
    {
      if (!forbidden.contains(std::make_tuple(i, curr, prev)))
        if (best_parent == -1 || dist[i][curr] < dist[best_parent][curr])
          best_parent = i;
    }

    prev = curr;
    curr = best_parent;
  }

  stack.push(0);
  io::cout << stack.size() - 1 << "\n";
  while (!stack.empty())
  {
    int u = stack.top();
    stack.pop();
    io::cout << u + 1 << " ";
  }

  io::cout << "\n";
}

} // namespace _59E

int main()
{
#ifdef ANTUMBRA
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
    io::cerr << "Input file not found\n";
    __builtin_trap();
  }

  size_t stack_size = 268435456;
  char *stack       = static_cast<char *>(std::malloc(stack_size));
  char *send        = stack + stack_size;
  send = reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(send) / 16 * 16);
  send -= 8;

  asm volatile("mov %%rsp, (%0)\n" : : "r"(send));
  asm volatile("mov %0, %%rsp\n" : : "r"(send - 8));
#endif

  int t{1};
  while (t-- > 0)
    _59E::run();

  io::cout.flush();

#ifdef ANTUMBRA
  asm volatile("mov (%0), %%rsp\n" : : "r"(send));
  std::free(stack);

  std::fclose(stdin);
#endif

  return 0;
}
