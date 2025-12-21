#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <climits>
#include <cmath>     // IWYU pragma: keep
#include <cstdint>   // IWYU pragma: keep
#include <cstring>   // IWYU pragma: keep
#include <iostream>  // IWYU pragma: keep
#include <string>    // IWYU pragma: keep
#include <utility>   // IWYU pragma: keep
#include <vector>    // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _RestaurantCustomers {

enum TimeType { OUTGOING, INCOMING };

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, TimeType>> times{};
  for (int i = 0, s, e; i < n; i++) {
    std::cin >> s >> e;
    times.push_back({s, TimeType::INCOMING});
    times.push_back({e, TimeType::OUTGOING});
  }

  std::sort(times.begin(), times.end());

  int mx{INT_MIN}, cur{};
  for (const auto& [p, t] : times) {
    if (t == TimeType::OUTGOING) {
      cur -= 1;
    } else {
      cur += 1;
    }

    mx = std::max(mx, cur);
  }

  std::cout << mx << "\n";
}

}  // namespace _RestaurantCustomers

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
    _RestaurantCustomers::run();

  std::cout.flush();

  return 0;
}
