#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <climits>
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

namespace _1146
{

auto run() -> void
{
  int N;
  std::cin >> N;

  int grid[101][101];

  for (int y = 0; y < N; y++)
    for (int x = 0; x < N; x++)
      std::cin >> grid[y][x];

  int prefix[101][101], vpsinc[101][101];
  prefix[0][0] = grid[0][0];

  for (int y = 1; y < N; y++)
    prefix[y][0] = prefix[y - 1][0] + grid[y][0];

  for (int x = 1; x < N; x++)
    prefix[0][x] = prefix[0][x - 1] + grid[0][x];

  for (int x = 0; x < N; x++)
    vpsinc[0][x] = grid[0][x];

  for (int x = 0; x < N; x++)
    for (int y = 1; y < N; y++)
      vpsinc[y][x] = vpsinc[y - 1][x] + grid[y][x];

  for (int y = 1; y < N; y++)
    for (int x = 1; x < N; x++)
      prefix[y][x] = prefix[y][x - 1] + vpsinc[y][x];

  auto sum = [&prefix](int y1, int y2, int x1, int x2) -> int {
    int tot = prefix[y2][x2];
    if (y1 != 0)
      tot -= prefix[y1 - 1][x2];
    if (x1 != 0)
      tot -= prefix[y2][x1 - 1];

    if (y1 != 0 && x1 != 0)
      tot += prefix[y1 - 1][x1 - 1];

    return tot;
  };

  int mx{INT_MIN};
  for (int y1 = 0; y1 < N; y1++)
    for (int y2 = y1; y2 < N; y2++)
      for (int x1 = 0; x1 < N; x1++)
        for (int x2 = x1; x2 < N; x2++)
          mx = std::max(mx, sum(y1, y2, x1, x2));

  std::cout << mx << "\n";
}

} // namespace _1146

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
    _1146::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
