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

namespace _E
{

auto run() -> void
{
  int h, w;
  std::cin >> h >> w;

  int a[h + 1][w + 1];
  std::memset(a, 0xcf, sizeof a);

  for (int y = 1; y <= h; y++)
    for (int x = 1; x <= w; x++)
      std::cin >> a[y][x];

  int64_t p[h + w];
  for (int i = 1; i <= h + w - 1; i++)
    std::cin >> p[i];

  int64_t min[h + w][h + 1][w + 1];
  std::memset(min, 0xcf, sizeof min);
  min[0][1][1] = 0;
  for (int day = 1; day <= h + w - 1; day++)
    for (int y = 1; y <= h; y++)
      for (int x = 1; x <= w; x++)
      {
        min[day][y][x] =
            std::max(min[day - 1][y - 1][x] + a[y - 1][x] - p[day],
                     min[day - 1][y][x - 1] + a[y][x - 1] - p[day]);
      }

  int64_t best{INT64_MIN};
  for (int y = 1; y <= h; y++)
    for (int x = 1; x <= w; x++)
      best = std::max(best, min[h + w - 1][y][x]);

  std::cout << -best << "\n";
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
  while (t-- > 0)
    _E::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
