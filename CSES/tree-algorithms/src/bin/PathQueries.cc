#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _PathQueries
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

  inline static auto log2(std::uint64_t n) -> std::uint64_t
  {
    return std::__lg(n);
  }

  constexpr inline static auto ceil_log2(std::uint64_t n) -> int
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

  inline static auto solve_linear(double a, double b, double c, double d,
                                  double e, double f) -> double *
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

  inline static auto solve_quadratic(double a, double b, double c) -> double *
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

template <typename T> struct SegmentTree
{
private:
  std::size_t offset_;
  std::unique_ptr<T[]> tree_;

  std::function<T(const T &, const T &)> function_;
  T defaultValue_;

public:
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
  int n, q;
  std::cin >> n >> q;

  int values[n];
  for (int i = 0; i < n; i++)
    std::cin >> values[i];

  std::vector<int> adj[n];
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    std::cin >> a >> b;

    adj[a - 1].push_back(b - 1);
    adj[b - 1].push_back(a - 1);
  }

  int count[n];
  auto dfs = [&adj, &count](auto &&dfs, int u, int p) -> void {
    count[u] = 1;
    for (const int &v : adj[u])
      if (v != p)
      {
        dfs(dfs, v, u);
        count[u] += count[v];
      }
  };

  dfs(dfs, 0, -1);

  int64_t path_sum[n], pos[n];
  std::vector<int> sizes{};
  auto dfs2 = [&adj, &path_sum, &count, &values, &pos,
               &sizes](auto &&dfs2, int u, int p) -> void {
    path_sum[u] = values[u];
    if (p != -1)
      path_sum[u] += path_sum[p];

    pos[u] = static_cast<int>(sizes.size());
    sizes.push_back(count[u]);
    for (const int &v : adj[u])
      if (v != p)
        dfs2(dfs2, v, u);
  };

  dfs2(dfs2, 0, -1);

  int64_t fps[n];
  for (int i = 0; i < n; ++i)
    fps[pos[i]] = path_sum[i];

  int64_t diff[n + 1];
  diff[n] = 0;
  diff[0] = fps[0];
  for (int i = 1; i < n; i++)
    diff[i] = fps[i] - fps[i - 1];

  auto SUM_SELECT = [](const int64_t &u, const int64_t &v) -> int64_t {
    return u + v;
  };

  SegmentTree<int64_t> tree(diff, n + 1, 0L, SUM_SELECT);
  while (q-- > 0)
  {
    int type;
    std::cin >> type;
    if (type == 1)
    {
      int s, x;
      std::cin >> s >> x;
      int sz        = sizes[pos[s - 1]];

      int64_t old   = values[s - 1];
      int64_t delta = x - old;

      values[s - 1] = x;
      diff[pos[s - 1]] += delta;
      diff[pos[s - 1] + sz] -= delta;
      tree.set_at_index(pos[s - 1], diff[pos[s - 1]]);
      tree.set_at_index(pos[s - 1] + sz, diff[pos[s - 1] + sz]);
    }
    else
    {
      int s;
      std::cin >> s;
      std::cout << tree.query_range(0, pos[s - 1] + 1) << "\n";
    }
  }
}

} // namespace _PathQueries

int main()
{
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef ANTUMBRA
  const rlim_t stack_size = 268435456;
  struct rlimit rl;

  int result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0 && rl.rlim_cur < stack_size)
  {
    rl.rlim_cur = stack_size;
    result      = setrlimit(RLIMIT_STACK, &rl);
    if (result != 0)
      std::cerr << "WARN: setrlimit failed\n";
  }

  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  while (t-- > 0)
    _PathQueries::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
