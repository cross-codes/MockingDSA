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

namespace _D
{

auto run() -> void
{
  int64_t n, m;
  std::cin >> n >> m;

  std::pair<int64_t, int64_t> xchg[m];
  for (int i = 0; i < m; i++)
    std::cin >> xchg[i].first >> xchg[i].second;

  auto SORT_ORDER = [](const std::pair<int64_t, int64_t> &a,
                       const std::pair<int64_t, int64_t> &b) -> bool {
    int64_t cmp = a.second - a.first - (b.second - b.first);
    if (cmp == 0)
      return a.first < b.first;
    else
      return cmp > 0;
  };

  std::sort(xchg, xchg + m, SORT_ORDER);

  int64_t cnt{}, x{n};
  for (int i = 0; i < m; i++)
  {
    int64_t y = xchg[i].first, z = xchg[i].second;

    if (x < y)
      continue;

    int64_t r = (x - y) / (y - z);
    if (x - (r * (y - z)) >= y)
      r += 1;

    cnt += r;
    x -= r * (xchg[i].first - xchg[i].second);
  }

  std::cout << cnt << "\n";
}

} // namespace _D

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
    _D::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
