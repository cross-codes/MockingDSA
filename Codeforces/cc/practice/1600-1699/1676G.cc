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

namespace _1676G
{

auto run() -> void
{
  int n;
  std::cin >> n;

  std::vector<int> adj[n];
  for (int i = 1; i < n; i++)
  {
    int u;
    std::cin >> u;
    adj[i].push_back(u - 1);
    adj[u - 1].push_back(i);
  }

  std::string colors;
  std::cin >> colors;

  int white[n + 1], black[n + 1], cnt{};
  auto dfs = [&cnt, &colors, &adj, &white, &black](auto &&dfs, int u,
                                                   int p) -> void {
    if (colors[u] == 'W')
    {
      white[u] = 1;
      black[u] = 0;
    }
    else
    {
      white[u] = 0;
      black[u] = 1;
    }

    for (const int &v : adj[u])
    {
      if (v != p)
      {
        dfs(dfs, v, u);
        white[u] += white[v];
        black[u] += black[v];
      }
    }

    if (black[u] == white[u])
      cnt += 1;
  };

  dfs(dfs, 0, -1);
  std::cout << cnt << "\n";
}

} // namespace _1676G

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
    _1676G::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
