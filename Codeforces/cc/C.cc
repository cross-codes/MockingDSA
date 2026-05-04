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

namespace _C {

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<int> a(n + 3, 0);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }

  auto safe = [&](int i, int j) -> bool {
    if (a[i] == a[j] || a[i] == 7 - a[j]) {
      return false;
    }

    return true;
  };

  auto assign = [](int e1, int e2, int e3, int e4) -> int {
    for (int i = 1; i <= 6; i++) {
      if (i != e1 && i != e2 && i != e3 && i != e4) {
        return i;
      }
    }

    __builtin_unreachable();
  };

  int cnt{};
  for (int i = 1; i <= n; i++) {
    if (!safe(i, i + 1)) {
      if (!safe(i + 1, i + 2)) {
        a[i + 1] = assign(a[i], 7 - a[i], a[i + 2], 7 - a[i + 2]);
        cnt += 1;
      } else {
        a[i] = assign(a[i + 1], 7 - a[i + 1], -1, -1);
        cnt += 1;
      }
    }
  }

  std::cout << cnt << "\n";
}

}  // namespace _C

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
    _C::run();

  std::cout.flush();

  return 0;
}
