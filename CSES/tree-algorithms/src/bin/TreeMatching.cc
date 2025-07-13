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

namespace _TreeMatching
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

  bool done[n];
  std::memset(done, false, sizeof done);

  int ans{};
  auto dfs = [&done, &ans, &adj](auto &&dfs, int u, int e) -> void {
    for (const int &v : adj[u])
    {
      if (v != e)
      {
        dfs(dfs, v, u);
        if (!done[u] && !done[v])
        {
          done[u] = done[v] = true;
          ans += 1;
        }
      }
    }
  };

  dfs(dfs, 0, -1);
  std::cout << ans << "\n";
}

} // namespace _TreeMatching

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
    _TreeMatching::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
