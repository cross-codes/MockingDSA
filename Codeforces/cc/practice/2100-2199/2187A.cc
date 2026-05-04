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

namespace _2187A {

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  int mx{INT_MIN}, mn{INT_MAX};
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    mx = std::max(mx, a[i]);
    mn = std::min(mn, a[i]);
  }

  std::vector<int> copy(a);
  std::sort(copy.begin(), copy.end());

  int res{INT_MAX};
  for (int i = 0; i < n; i++) {
    if (a[i] != copy[i]) {
      res = std::min(res, std::max(a[i] - mn, mx - a[i]));
    }
  }

  std::cout << (res == INT_MAX ? -1 : res) << "\n";
}

}  // namespace _2187A

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
    _2187A::run();

  std::cout.flush();

  return 0;
}
