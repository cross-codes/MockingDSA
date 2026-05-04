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

namespace _MaximumSubarraySumII {

auto run() -> void {
  int n, a, b;
  std::cin >> n >> a >> b;

  std::vector<int64_t> prefix(n + 1);
  for (int i = 1, x; i <= n; i++) {
    std::cin >> x;
    prefix[i] = prefix[i - 1] + x;
  }

  std::multiset<int64_t> prefix_store{};
  int64_t mx{INT64_MIN};
  for (int i = a; i <= n; i++) {
    prefix_store.insert(prefix[i - a]);
    if (i >= b + 1) [[likely]] {
      prefix_store.erase(prefix_store.find(prefix[i - b - 1]));
    }

    mx = std::max(mx, prefix[i] - *prefix_store.begin());
  }

  std::cout << mx << "\n";
}

}  // namespace _MaximumSubarraySumII

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
    _MaximumSubarraySumII::run();

  std::cout.flush();

  return 0;
}
