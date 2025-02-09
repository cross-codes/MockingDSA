#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>

using usize = size_t;
using ssize = ptrdiff_t;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

auto constexpr TUPLE_ORDER = [](const std::tuple<int, int, int> &a,
                                const std::tuple<int, int, int> &b) -> bool {
  return std::get<1>(a) < std::get<1>(b);
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ssize n;
  std::cin >> n;

  std::unique_ptr<ssize[]> compatible(new ssize[n + 1]);
  std::unique_ptr<i64[]> maxCost(new i64[n + 1]);
  std::unique_ptr<std::tuple<int, int, int>[]> intervals(
      new std::tuple<int, int, int>[n + 1]);

  for (ssize i = 1; i <= n; i++) {
    int start, end, cost;
    std::cin >> start >> end >> cost;
    intervals[i] = std::make_tuple(start, end, cost);
  }

  std::sort(&intervals[1], &intervals[n + 1], ::TUPLE_ORDER);

  for (ssize i = 1; i <= n; i++) {
    int start = std::get<0>(intervals[i]);
    auto it = std::lower_bound(&intervals[1], &intervals[n + 1],
                               std::make_tuple(0, start, 0), ::TUPLE_ORDER);

    compatible[i] = std::distance(&intervals[1], --it) + 1;
  }

  for (ssize i = 1; i <= n; i++) {
    int cost = std::get<2>(intervals[i]);
    maxCost[i] = std::max(cost + maxCost[compatible[i]], maxCost[i - 1]);
  }

  std::cout << maxCost[n] << "\n";

  return 0;
}
