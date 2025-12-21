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

namespace _ConcertTickets {

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::multiset<int> prices{};
  for (int i = 0, h; i < n; i++) {
    std::cin >> h;
    prices.insert(h);
  }

  for (int i = 0, t; i < m; i++) {
    std::cin >> t;
    auto it = prices.upper_bound(t);
    if (it == prices.begin()) {
      std::cout << "-1\n";
    } else {
      auto prev = std::prev(it);
      std::cout << *prev << "\n";
      prices.erase(prev);
    }
  }
}

}  // namespace _ConcertTickets

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
    _ConcertTickets::run();

  std::cout.flush();

  return 0;
}
