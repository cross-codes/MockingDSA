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
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _22E
{

auto run() -> void
{
  int n;
  std::cin >> n;

  std::vector<int> adj[n], adjT[n];
  std::vector<std::pair<int, int>> edges{};
  for (int i = 0; i < n; i++)
  {
    int a;
    std::cin >> a;
    adj[i].push_back(a - 1);
    adjT[a - 1].push_back(i);
    edges.emplace_back(i, a - 1);
  }

  std::vector<int> order{};
  bool visited[n];
  std::memset(visited, false, sizeof visited);

  auto dfs = [&visited, &adj, &order](auto &&dfs, int u) -> void {
    visited[u] = true;

    for (const int &v : adj[u])
      if (!visited[v])
        dfs(dfs, v);

    order.push_back(u);
  };

  for (int u = 0; u < n; u++)
    if (!visited[u])
      dfs(dfs, u);

  std::reverse(order.begin(), order.end());

  std::unordered_map<int, int> rep{}, inv{};
  auto dfsT = [&visited, &adjT, &rep](auto &&dfsT, int u, int cc) -> void {
    visited[u] = true;
    rep[u]     = cc;

    for (const int &v : adjT[u])
      if (!visited[v])
        dfsT(dfsT, v, cc);
  };

  std::memset(visited, false, sizeof visited);

  std::vector<int> ccr{};
  for (int i : order)
    if (!visited[i])
    {
      int cc  = static_cast<int>(ccr.size());
      inv[cc] = i;
      dfsT(dfsT, i, cc);
      ccr.push_back(i);
    }

  if (ccr.empty() || ccr.size() == 1)
  {
    std::cout << "0\n";
    return;
  }

  int N = static_cast<int>(ccr.size());

  int scc_in[N], scc_out[N];
  std::memset(scc_in, 0x00, sizeof scc_in);
  std::memset(scc_out, 0x00, sizeof scc_out);

  for (const auto &[u, v] : edges)
  {
    if (rep[u] != rep[v])
    {
      scc_out[rep[u]] += 1;
      scc_in[rep[v]] += 1;
    }
  }

  std::vector<int> sources{}, sinks{};
  for (int i = 0; i < N; i++)
  {
    if (scc_in[i] == 0)
      sources.push_back(i);
    if (scc_out[i] == 0)
      sinks.push_back(i);
  }

  int E = static_cast<int>(std::max(sources.size(), sinks.size()));

  std::cout << E << "\n";
  for (int i = 0; i < E; i++)
  {
    int u = inv[sinks[i % sinks.size()]];
    int v = inv[sources[(i + 1) % sources.size()]];
    std::cout << std::format("{} {}\n", u + 1, v + 1);
  }
}

} // namespace _22E

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
    _22E::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
