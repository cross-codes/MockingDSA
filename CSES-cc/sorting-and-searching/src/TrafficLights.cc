#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <set>
#include <string>   // IWYU pragma: keep
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _TrafficLights {

auto run() -> void {
  int x, n;
  std::cin >> x >> n;

  const auto SIZED = [](const std::pair<int, int>& a,
                        const std::pair<int, int>& b) -> bool {
    return (a.second - a.first == b.second - b.first
                ? a.first < b.first
                : a.second - a.first < b.second - b.first);
  };

  std::set<std::pair<int, int>> sorted_intervals{};
  std::set<std::pair<int, int>, decltype(SIZED)> intervals_by_size{};

  sorted_intervals.insert({0, x});
  intervals_by_size.insert({0, x});

  for (int i = 0, p; i < n; i++) {
    std::cin >> p;

    auto [s, e] = *(std::prev(sorted_intervals.upper_bound({p, -1})));

    sorted_intervals.erase({s, e});
    intervals_by_size.erase({s, e});

    std::pair<int, int> left  = std::make_pair(s, p);
    std::pair<int, int> right = std::make_pair(p, e);
    sorted_intervals.insert(left);
    intervals_by_size.insert(left);

    sorted_intervals.insert(right);
    intervals_by_size.insert(right);

    auto largest = *intervals_by_size.rbegin();
    std::cout << largest.second - largest.first << " ";
  }

  std::cout << "\n";
}

}  // namespace _TrafficLights

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef EVERMORE
  pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);

  FILE* stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  while (t-- > 0)
    _TrafficLights::run();

  std::cout.flush();

  return 0;
}
