#pragma GCC target("popcnt")
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

namespace _CornerSubgridCount
{

auto run() -> void
{
  int n;
  std::cin >> n;

  uint64_t grid[n][n / 60 + 1];
  for (int i = 0; i < n; i++)
  {
    std::string row{};
    std::cin >> row;

    for (int j = 0; j <= n / 60; j++)
    {
      if (static_cast<int>(row.length()) == 60 * j)
        grid[i][j] = 0;
      else
        grid[i][j] = std::stoll(row.substr(60 * j, 60), 0, 2);
    }
  }

  int64_t gcnt{};
  for (int a = 0; a < n; a++)
  {
    for (int b = a + 1; b < n; b++)
    {
      int64_t cnt{};
      for (int i = 0; i <= n / 60; i++)
        cnt += std::popcount(grid[a][i] & grid[b][i]);
      gcnt += (cnt * (cnt - 1)) >> 1;
    }
  }

  std::cout << gcnt << "\n";
}

} // namespace _CornerSubgridCount

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
    _CornerSubgridCount::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
