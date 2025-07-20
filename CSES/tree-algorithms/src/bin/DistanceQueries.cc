#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <functional>
#include <iostream>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _DistanceQueries
{

template <typename T> struct IdempotentSparseTable
{
private:
  std::function<T(const T &, const T &)> function_;
  std::vector<std::vector<T>> table;

public:
  IdempotentSparseTable(std::function<T(const T &, const T &)> func, T array[],
                        std::size_t n)
      : function_(func)
  {
    std::size_t K = std::__lg(n);

    table.resize(K + 1, std::vector<T>(n));
    std::copy(array, array + n, table[0].begin());

    for (std::size_t y = 1; y < table.size(); y++)
      for (std::size_t x = 0, k = 1 << (y - 1); x <= n - (1 << y); x++, k++)
        table[y][x] = function_(table[y - 1][x], table[y - 1][k]);
  }

  T query_range(std::size_t from_idx, std::size_t past_end_idx)
  {
    std::size_t row = std::__lg(past_end_idx - from_idx);
    return function_(table[row][from_idx],
                     table[row][past_end_idx - (1 << row)]);
  }
};

auto run() -> void
{
  int n, q;
  std::cin >> n >> q;

  std::vector<int> adj[n];
  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    std::cin >> u >> v;

    adj[u - 1].push_back(v - 1);
    adj[v - 1].push_back(u - 1);
  }

  int pos[n];

  std::vector<int> id, depth{};
  auto dfs = [&id, &pos, &adj, &depth](auto &&dfs, int u, int p) -> void {
    pos[u] = static_cast<int>(id.size());
    id.push_back(u);
    if (depth.size() > 0)
      depth.push_back(depth.back() + 1);
    else
      depth.push_back(0);

    for (const int &v : adj[u])
    {
      if (v != p)
      {
        dfs(dfs, v, u);
        id.push_back(u);
        depth.push_back(depth.back() - 1);
      }
    }
  };

  dfs(dfs, 0, -1);

  auto MIN_SELECT = [](const int &u, const int &v) -> int {
    return std::min(u, v);
  };

  IdempotentSparseTable<int> table(MIN_SELECT, depth.data(), depth.size());

  while (q-- > 0)
  {
    int a, b;
    std::cin >> a >> b;
    a -= 1, b -= 1;
    int posa = pos[a], posb = pos[b];
    int deptha = depth[posa], depthb = depth[posb];
    int depthc{};
    if (posa < posb)
      depthc = table.query_range(posa, posb + 1);
    else
      depthc = table.query_range(posb, posa + 1);

    std::cout << deptha + depthb - (depthc << 1) << "\n";
  }
}

} // namespace _DistanceQueries

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
    _DistanceQueries::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
