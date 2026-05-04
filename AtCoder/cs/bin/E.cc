#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <set>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _E
{

auto run() -> void
{
  int n, m, x, y;
  std::cin >> n >> m >> x >> y;

  std::multiset<int> adj[n];
  for (int i = 0; i < m; i++)
  {
    int u, v;
    std::cin >> u >> v;
    adj[u - 1].insert(v - 1);
    adj[v - 1].insert(u - 1);
  }

  int p[n];
  std::memset(p, -1, sizeof p);

  bool bad[n];
  std::memset(bad, false, sizeof bad);

  bool visited[n];
  std::memset(visited, false, sizeof visited);

  // dfs?
  auto dfs = [&y, &p, &bad, &visited, &adj](auto &&dfs, int u,
                                            bool &terminate) -> void {
    if (terminate)
      return;

    if (u == y - 1)
    {
      terminate = true;
      return;
    }

    visited[u] = true;
    for (const int &v : adj[u])
    {
      if (terminate)
        return;

      if (!visited[v] && !bad[v])
      {
        p[v] = u;
        dfs(dfs, v, terminate);
        if (terminate)
          return;

        bad[v]     = true;
        visited[v] = false;
        p[v]       = -1;
      }
    }
  };

  bool terminate{};
  dfs(dfs, x - 1, terminate);

  std::vector<int> path{};
  int curr = y - 1;
  path.push_back(curr);
  while (curr != x - 1)
  {
    curr = p[curr];
    path.push_back(curr);
  }

  std::reverse(path.begin(), path.end());
  for (int e : path)
    std::cout << 1 + e << " ";

  std::cout << "\n";
}

} // namespace _E

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
  std::cin >> t;
  while (t-- > 0)
    _E::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
