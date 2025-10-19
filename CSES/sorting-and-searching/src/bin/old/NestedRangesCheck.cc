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

namespace _NestedRangesCheck
{

auto run() -> void
{
  int n;
  std::cin >> n;

  std::tuple<int, int, int> intervals[n];
  for (int i = 0; i < n; i++)
  {
    int s, e;
    std::cin >> s >> e;
    intervals[i] = std::make_tuple(s, e, i);
  }

  std::pair<int, int> res[n];

  auto CASE_ONE = [](const std::tuple<int, int, int> &a,
                     const std::tuple<int, int, int> &b) -> bool {
    int cmp = std::get<0>(a) - std::get<0>(b);
    if (cmp == 0)
      return std::get<1>(a) < std::get<1>(b);
    else
      return cmp > 0;
  };

  std::sort(intervals, intervals + n, CASE_ONE);

  int mnr{INT_MAX};
  for (int i = 0; i < n; i++)
  {
    if (std::get<1>(intervals[i]) < mnr)
    {
      res[std::get<2>(intervals[i])].first = 0;
      mnr                                  = std::get<1>(intervals[i]);
    }
    else
      res[std::get<2>(intervals[i])].first = 1;
  }

  auto CASE_TWO = [](const std::tuple<int, int, int> &a,
                     const std::tuple<int, int, int> &b) -> bool {
    int cmp = std::get<0>(a) - std::get<0>(b);
    if (cmp == 0)
      return std::get<1>(a) > std::get<1>(b);
    else
      return cmp < 0;
  };

  std::sort(intervals, intervals + n, CASE_TWO);

  int mxr{INT_MIN};
  for (int i = 0; i < n; i++)
  {
    if (std::get<1>(intervals[i]) > mxr)
    {
      res[std::get<2>(intervals[i])].second = 0;
      mxr                                   = std::get<1>(intervals[i]);
    }
    else
      res[std::get<2>(intervals[i])].second = 1;
  }

  for (int i = 0; i < n; i++)
    std::cout << res[i].first << " ";

  std::cout << "\n";

  for (int i = 0; i < n; i++)
    std::cout << res[i].second << " ";

  std::cout << "\n";
}

} // namespace _NestedRangesCheck

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
    _NestedRangesCheck::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
