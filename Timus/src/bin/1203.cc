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

namespace _1203
{

auto run() -> void
{
  int N;
  std::cin >> N;

  std::pair<int, int> intervals[N];
  for (int i = 0; i < N; i++)
  {
    int s, e;
    std::cin >> s >> e;

    intervals[i] = {s, e};
  }

  auto INTERVAL_ORDER = [](const std::pair<int, int> &a,
                           const std::pair<int, int> &b) -> bool {
    int cmp = a.second - b.second;
    if (cmp == 0)
      return a.first > b.first;
    else
      return cmp < 0;
  };

  std::sort(intervals, intervals + N, INTERVAL_ORDER);

  int compat[N];
  for (int i = 0; i < N; i++)
  {
    auto [s, _] = intervals[i];
    auto it     = std::lower_bound(intervals, intervals + N,
                                   std::make_pair(INT_MAX, s), INTERVAL_ORDER);

    if (it != intervals)
    {
      it        = std::prev(it);
      compat[i] = static_cast<int>(std::distance(intervals, it));
    }
    else
      compat[i] = -1;
  }

  int t[N + 1];
  t[0] = 0;
  for (int i = 1; i <= N; i++)
    t[i] = std::max({1, t[i - 1], t[compat[i - 1] + 1] + 1});

  std::cout << t[N] << "\n";
}

} // namespace _1203

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
    _1203::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
