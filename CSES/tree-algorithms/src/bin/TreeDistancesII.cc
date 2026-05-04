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

namespace _TreeDistancesII
{

auto run() -> void
{
  int n;
  std::cin >> n;

  std::vector<int> adj[n];
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    std::cin >> a >> b;
    adj[a - 1].push_back(b - 1);
    adj[b - 1].push_back(a - 1);
  }

  int64_t sumdist[n], count[n];
  std::memset(sumdist, 0x00, sizeof sumdist);

  auto dfs0 = [&adj, &sumdist, &count](auto &&dfs0, int u, int p,
                                       int depth) -> void {
    sumdist[0] += depth;
    count[u] = 1;
    for (const int &v : adj[u])
      if (v != p)
      {
        dfs0(dfs0, v, u, depth + 1);
        count[u] += count[v];
      }
  };

  dfs0(dfs0, 0, -1, 0);

  auto dfs1 = [&adj, &sumdist, &n, &count](auto &&dfs1, int u, int p) -> void {
    for (const int &v : adj[u])
      if (v != p)
      {
        sumdist[v] = sumdist[u] + n - 2 * count[v];
        dfs1(dfs1, v, u);
      }
  };

  dfs1(dfs1, 0, -1);

  for (int64_t e : sumdist)
    std::cout << e << " ";

  std::cout << "\n";
}

} // namespace _TreeDistancesII

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
    _TreeDistancesII::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
