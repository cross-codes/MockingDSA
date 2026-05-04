#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
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

namespace _862B
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

  // 0 grey. 1 black
  int colors[n];
  std::memset(colors, -1, sizeof colors);

  std::vector<int> grey{}, black{};
  auto dfs = [&adj, &colors, &grey, &black](auto &&dfs, int u, int p) -> void {
    if (p != -1)
    {
      if (colors[p] == 1)
      {
        colors[u] = 0;
        grey.push_back(u);
      }
      else
      {
        colors[u] = 1;
        black.push_back(u);
      }
    }

    for (const int &v : adj[u])
      if (v != p)
        dfs(dfs, v, u);
  };

  colors[0] = 1;
  black.push_back(0);
  dfs(dfs, 0, -1);
  std::cout << grey.size() * black.size() - (n - 1) << "\n";
}

} // namespace _862B

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
    _862B::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
