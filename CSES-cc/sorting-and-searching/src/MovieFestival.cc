#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <utility>    // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _MovieFestival {

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> movies(n);
  for (int i = 0; i < n; i++) {
    std::cin >> movies[i].first >> movies[i].second;
  }

  auto INTERVAL_ORDER = [](const std::pair<int, int>& a,
                           const std::pair<int, int>& b) -> bool {
    return (a.second == b.second) ? a.first < b.first : a.second < b.second;
  };

  std::sort(movies.begin(), movies.end(), INTERVAL_ORDER);

  int mx{}, cur{}, cure{};
  for (const auto& [s, e] : movies) {
    if (s >= cure) {
      cure = e, cur += 1;
      mx   = std::max(mx, cur);
    }
  }

  std::cout << mx << "\n";
}

}  // namespace _MovieFestival

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
    _MovieFestival::run();

  std::cout.flush();

  return 0;
}
