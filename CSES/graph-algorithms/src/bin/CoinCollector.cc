#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _CoinCollector
{

auto run() -> void
{
  int n, m;
  std::cin >> n >> m;

  int k[n];
  for (int i = 0; i < n; i++)
    std::cin >> k[i];

  std::vector<int> adj[n], adjT[n];
  std::vector<std::pair<int, int>> edges{};
  for (int i = 0; i < m; i++)
  {
    int a, b;
    std::cin >> a >> b;
    adj[a - 1].push_back(b - 1);
    adjT[b - 1].push_back(a - 1);
    edges.emplace_back(a - 1, b - 1);
  }

  bool visited[n];
  std::memset(visited, false, sizeof visited);

  std::vector<int> order{};
  auto dfs = [&order, &adj, &visited](auto &&dfs, int u) -> void {
    visited[u] = true;
    for (const int &v : adj[u])
      if (!visited[v])
        dfs(dfs, v);

    order.push_back(u);
  };

  for (int i = 0; i < n; i++)
    if (!visited[i])
      dfs(dfs, i);

  std::reverse(order.begin(), order.end());

  std::memset(visited, false, sizeof visited);
  std::unordered_map<int, int> scc{};
  auto dfsR = [&visited, &scc, &k, &adjT](auto &&dfsR, int u, int64_t &cc_sum,
                                          int cc) -> void {
    visited[u] = true;
    cc_sum += k[u];
    scc[u] = cc;
    for (const int &v : adjT[u])
      if (!visited[v])
        dfsR(dfsR, v, cc_sum, cc);
  };

  int cc{};
  std::unordered_map<int, int64_t> sums{};
  for (int u : order)
    if (!visited[u])
    {
      int64_t cc_sum{};
      dfsR(dfsR, u, cc_sum, cc);
      sums[cc] = cc_sum;
      cc += 1;
    }

  std::unordered_set<int> scc_adj[cc];
  for (const auto &[u, v] : edges)
  {
    int ccu = scc[u], ccv = scc[v];
    if (!scc_adj[ccu].contains(ccv))
      scc_adj[ccu].insert(ccv);
  }

  bool cc_visited[cc];
  std::memset(cc_visited, false, sizeof cc_visited);
  std::vector<int> cc_order{};

  auto dfsC = [&cc_order, &cc_visited, &scc_adj](auto &&dfsC, int ccu) -> void {
    cc_visited[ccu] = true;
    for (const int &ccv : scc_adj[ccu])
      if (!cc_visited[ccv])
        dfsC(dfsC, ccv);

    cc_order.push_back(ccu);
  };

  for (int icc = 0; icc < cc; icc++)
    if (!cc_visited[icc])
      dfsC(dfsC, icc);

  std::reverse(cc_order.begin(), cc_order.end());
  int64_t mxc[cc];
  for (int icc = 0; icc < cc; icc++)
    mxc[icc] = sums[icc];

  for (int ccu : cc_order)
    for (const int &ccv : scc_adj[ccu])
      mxc[ccv] = std::max(mxc[ccv], mxc[ccu] + sums[ccv]);

  std::cout << *std::max_element(mxc, mxc + cc) << "\n";
}

} // namespace _CoinCollector

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
    _CoinCollector::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
