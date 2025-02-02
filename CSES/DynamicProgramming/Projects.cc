#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sys/types.h>
#include <tuple>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 200001;
std::tuple<int, int, int> intervals[_];
ssize_t compatible[_];
i64 maxCost[_];

auto constexpr TUPLE_ORDER = [](const std::tuple<int, int, int> &a,
                                const std::tuple<int, int, int> &b) -> bool {
  return std::get<1>(a) < std::get<1>(b);
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  std::cin >> n;

  for (size_t i = 1; i <= n; i++) {
    int start, end, cost;
    std::cin >> start >> end >> cost;
    ::intervals[i] = std::make_tuple(start, end, cost);
  }

  std::sort(&::intervals[1], &::intervals[n + 1], ::TUPLE_ORDER);

  for (size_t i = 1; i <= n; i++) {
    int start = std::get<0>(::intervals[i]);
    auto it = std::lower_bound(&::intervals[1], &::intervals[n + 1],
                               std::make_tuple(0, start, 0), ::TUPLE_ORDER);

    ::compatible[i] = std::distance(&::intervals[1], --it) + 1;
  }

  for (size_t i = 1; i <= n; i++) {
    int cost = std::get<2>(::intervals[i]);
    ::maxCost[i] = std::max(cost + ::maxCost[compatible[i]], ::maxCost[i - 1]);
  }

  std::cout << ::maxCost[n] << "\n";

  return 0;
}
