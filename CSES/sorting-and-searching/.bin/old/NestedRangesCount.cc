#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <climits>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _NestedRangesCount
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

  __gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type, std::less<>,
                   __gnu_pbds::rb_tree_tag,
                   __gnu_pbds::tree_order_statistics_node_update>
      ost1{};

  int gcnt{};
  for (int i = 0; i < n; i++)
  {
    auto [s, e, idx] = intervals[i];
    res[idx].first   = static_cast<int>(ost1.order_of_key({e, INT_MAX}));
    ost1.insert({e, gcnt++});
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

  __gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type, std::less<>,
                   __gnu_pbds::rb_tree_tag,
                   __gnu_pbds::tree_order_statistics_node_update>
      ost2{};

  gcnt = 0;
  for (int i = 0; i < n; i++)
  {
    auto [s, e, idx] = intervals[i];
    res[idx].second  = static_cast<int>(ost2.order_of_key({INT_MAX, INT_MAX}) -
                                        ost2.order_of_key({e, INT_MIN}));
    ost2.insert({e, gcnt++});
  }

  for (int i = 0; i < n; i++)
    std::cout << res[i].first << " ";

  std::cout << "\n";

  for (int i = 0; i < n; i++)
    std::cout << res[i].second << " ";

  std::cout << "\n";
}

} // namespace _NestedRangesCount

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
    _NestedRangesCount::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
