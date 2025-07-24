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

namespace _HamiltonianFlights
{

constexpr int MOD = static_cast<int>(1e9 + 7);

auto run() -> void
{
  int n, m;
  std::cin >> n >> m;

  std::vector<int> adjT[n];
  for (int i = 0; i < m; i++)
  {
    int u, v;
    std::cin >> u >> v;
    adjT[v - 1].push_back(u - 1);
  }

  int possible[1 << 20][20]{};
  possible[1][0] = 1;
  for (int s = 0; s < 1 << n; s++)
  {
    if ((s & 1) == 0)
      continue;

    if (s & (1 << (n - 1)) && s != (1 << n) - 1)
      continue;

    for (int i = 0; i < n; i++)
    {
      if ((s & (1 << i)) == 0)
        continue;

      for (int v : adjT[i])
      {
        if (s & (1 << v))
        {
          possible[s][i] += possible[s ^ (1 << i)][v];
          possible[s][i] %= MOD;
        }
      }
    }
  }

  std::cout << possible[(1 << n) - 1][n - 1] << "\n";
}

} // namespace _HamiltonianFlights

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
    _HamiltonianFlights::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
