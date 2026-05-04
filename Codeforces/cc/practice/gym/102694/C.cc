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
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _C
{

auto run() -> void
{
  int n;
  std::cin >> n;

  std::vector<int> adj[n];
  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    std::cin >> u >> v;
    adj[u - 1].push_back(v - 1);
    adj[v - 1].push_back(u - 1);
  }

  int succ[n][20];
  for (int i = 0; i < 20; i++)
    succ[0][i] = -1;

  int depth[n];
  std::memset(depth, 0x00, sizeof depth);

  auto dfs = [&succ, &adj, &depth](auto &&dfs, int u, int p) -> void {
    for (const int &v : adj[u])
      if (v != p)
      {
        succ[v][0] = u;
        depth[v]   = depth[u] + 1;
        dfs(dfs, v, u);
      }
  };

  dfs(dfs, 0, -1);

  for (int i = 1; i < 20; i++)
    for (int j = 0; j < n; j++)
      if (succ[j][i - 1] == -1)
        succ[j][i] = -1;
      else
        succ[j][i] = succ[succ[j][i - 1]][i - 1];

  auto ancestor = [&succ](int u, int k) {
    int curr = u;
    while (k != 0)
    {
      int pos = __builtin_ctz(k);
      curr    = succ[curr][pos];
      if (curr == -1)
        return curr;
      k &= (k - 1);
    }

    return curr;
  };

  auto LCA = [&ancestor, &succ, &depth](int u, int v) {
    if (depth[u] < depth[v])
      std::swap(u, v);

    u = ancestor(u, depth[u] - depth[v]);
    if (u == v)
      return u;

    for (int i = 19; i >= 0; i--)
      if (succ[u][i] != succ[v][i])
      {
        u = succ[u][i];
        v = succ[v][i];
      }

    return succ[u][0];
  };

  int q;
  std::cin >> q;
  while (q-- > 0)
  {
    int a, b, c;
    std::cin >> a >> b >> c;
    a -= 1, b -= 1;

    int lca = LCA(a, b);

    if (depth[a] - depth[lca] < c)
    {
      c -= depth[a] - depth[lca];
      if (depth[b] - depth[lca] < c)
        std::cout << b + 1 << "\n";
      else
      {
        int dist = depth[b] - depth[lca] - c;
        std::cout << ancestor(b, dist) + 1 << "\n";
      }
    }
    else
    {
      std::cout << ancestor(a, c) + 1 << "\n";
    }
  }
}

} // namespace _C

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
    _C::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
