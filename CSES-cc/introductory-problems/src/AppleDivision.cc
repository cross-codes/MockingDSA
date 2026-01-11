#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <concepts>   // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <deque>      // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <map>        // IWYU pragma: keep
#include <memory>     // IWYU pragma: keep
#include <numeric>
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

namespace _AppleDivision {

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<int> p(n);
  for (int i = 0; i < n; i++) {
    std::cin >> p[i];
  }

  int64_t tot = std::accumulate(p.begin(), p.end(), INT64_C(0));

  int64_t subset_sum{}, best_diff = 9223372036854775807LL;
  for (int mask = 0; mask < (1 << n); mask++) {
    subset_sum = 0;
    for (int i = 0; i < n; i++) {
      if (mask & (1 << i)) {
        subset_sum += p[i];
      }
    }

    best_diff = std::min(best_diff, std::abs(tot - (subset_sum << 1)));
  }

  std::cout << best_diff << "\n";
}

}  // namespace _AppleDivision

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
    _AppleDivision::run();

  std::cout.flush();

  return 0;
}
