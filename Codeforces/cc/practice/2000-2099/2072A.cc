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

namespace _A {

// Was struggling with the negative case for some reason (locked thinking?)
auto run() -> void {
  int n, k, p;
  std::cin >> n >> k >> p;

  if (k < 0) {
    int cursum{}, steps{};
    for (int i = 0; i < n; i++) {
      if (cursum == k) {
        std::cout << steps << "\n";
        return;
      }

      cursum += std::max(k - cursum, -p);
      steps += 1;
    }

    if (cursum == k) {
      std::cout << steps << "\n";
      return;
    }

    std::cout << "-1\n";
  } else {
    int cursum{}, steps{};
    for (int i = 0; i < n; i++) {
      if (cursum == k) {
        std::cout << steps << "\n";
        return;
      }

      cursum += std::min(k - cursum, p);
      steps += 1;
    }

    if (cursum == k) {
      std::cout << steps << "\n";
      return;
    }

    std::cout << "-1\n";
  }
}

}  // namespace _A

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
  std::cin >> t;
  while (t-- > 0)
    _A::run();

  std::cout.flush();

  return 0;
}
