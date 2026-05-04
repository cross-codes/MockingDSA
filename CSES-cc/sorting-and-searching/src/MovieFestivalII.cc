#include <algorithm>      // IWYU pragma: keep
#include <array>          // IWYU pragma: keep
#include <bit>            // IWYU pragma: keep
#include <cassert>        // IWYU pragma: keep
#include <cmath>          // IWYU pragma: keep
#include <concepts>       // IWYU pragma: keep
#include <cstdint>        // IWYU pragma: keep
#include <cstring>        // IWYU pragma: keep
#include <deque>          // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <map>            // IWYU pragma: keep
#include <memory>         // IWYU pragma: keep
#include <set>            // IWYU pragma: keep
#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <utility>        // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _MovieFestivalII {

auto run() -> void {
  int n, k;
  std::cin >> n >> k;

  std::vector<std::pair<int, int>> movies(n);
  for (int i = 0; i < n; i++) {
    std::cin >> movies[i].first >> movies[i].second;
  }

  auto INTERVAL_ORDER = [](const std::pair<int, int>& a,
                           const std::pair<int, int>& b) -> bool {
    return (a.second == b.second) ? a.first < b.first : a.second < b.second;
  };

  std::sort(movies.begin(), movies.end(), INTERVAL_ORDER);

  std::multiset<int> times{};
  for (int i = 0; i < k; i++) {
    times.insert(0);
  }

  int mx{};
  for (const auto& [s, e] : movies) {
    auto it = times.upper_bound(s);
    if (it != times.begin()) {
      times.erase(std::prev(it));
      times.insert(e);
      mx += 1;
    }
  }

  std::cout << mx << "\n";
}

}  // namespace _MovieFestivalII

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
    _MovieFestivalII::run();

  std::cout.flush();

  return 0;
}
