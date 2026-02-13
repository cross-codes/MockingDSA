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

namespace _BookShop {

auto run() -> void {
  int n, x;
  std::cin >> n >> x;

  std::vector<int> h(n + 1), s(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> h[i];
  }

  for (int i = 1; i <= n; i++) {
    std::cin >> s[i];
  }

  std::vector<int> mx(x + 1, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = x; j >= h[i]; j--) {
      mx[j] = std::max(mx[j], mx[j - h[i]] + s[i]);
    }
  }

  std::cout << mx[x] << "\n";
}

}  // namespace _BookShop

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
    _BookShop::run();

  std::cout.flush();

  return 0;
}
