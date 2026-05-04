#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <concepts>   // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <deque>      // IWYU pragma: keep
#include <format>
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

namespace _SumOfFourValues {

auto run() -> void {
  int n;
  std::cin >> n;

  int64_t x;
  std::cin >> x;

  std::vector<std::pair<int, int>> a(n);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i - 1].first;
    a[i - 1].second = i;
  }

  std::sort(a.begin(), a.end());

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      long pref = a[i].first + a[j].first;
      if (pref > x) {
        break;
      }

      int l = j + 1, r = n - 1;
      while (l < r) {
        long suff = a[l].first + a[r].first;
        if (pref + suff > x) {
          r -= 1;
        } else if (pref + suff < x) {
          l += 1;
        } else {
          std::cout << std::format("{} {} {} {}\n", a[i].second, a[j].second,
                                   a[l].second, a[r].second);
          return;
        }
      }
    }
  }

  std::cout << "IMPOSSIBLE\n";
}

}  // namespace _SumOfFourValues

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
    _SumOfFourValues::run();

  std::cout.flush();

  return 0;
}
