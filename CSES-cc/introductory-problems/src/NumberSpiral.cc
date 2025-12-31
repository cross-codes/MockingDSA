#include <algorithm>      // IWYU pragma: keep
#include <array>          // IWYU pragma: keep
#include <bit>            // IWYU pragma: keep
#include <cassert>        // IWYU pragma: keep
#include <cmath>          // IWYU pragma: keep
#include <cstdint>        // IWYU pragma: keep
#include <cstring>        // IWYU pragma: keep
#include <deque>          // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <utility>        // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _NumberSpiral {

auto run() -> void {
  int y, x;
  std::cin >> y >> x;

  int64_t r{std::max(y, x) - 1}, res;
  if (r & 1) {
    if (y < x) {
      res = r * r + y;
    } else {
      res = r * r + 2 * r - x + 2;
    }
  } else {
    if (y < x) {
      res = r * r + 2 * r - y + 2;
    } else {
      res = r * r + x;
    }
  }

  std::cout << res << "\n";
}

}  // namespace _NumberSpiral

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
    _NumberSpiral::run();

  std::cout.flush();

  return 0;
}
