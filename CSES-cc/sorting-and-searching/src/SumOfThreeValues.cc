#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <format>
#include <iostream>  // IWYU pragma: keep
#include <string>    // IWYU pragma: keep
#include <utility>   // IWYU pragma: keep
#include <vector>    // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _SumOfThreeValues {

auto run() -> void {
  int n, x;
  std::cin >> n >> x;

  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].first;
    a[i].second = i + 1;
  }

  std::sort(a.begin(), a.end());

  for (int i = 0; i < n; i++) {
    int l = i + 1, r = n - 1, target = x - a[i].first;
    while (l < r) {
      if (a[l].first + a[r].first < target) {
        l += 1;
      } else if (a[l].first + a[r].first > target) {
        r -= 1;
      } else {
        std::cout << std::format("{} {} {}\n", a[i].second, a[l].second,
                                 a[r].second);
        return;
      }
    }
  }

  std::cout << "IMPOSSIBLE\n";
}

}  // namespace _SumOfThreeValues

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
    _SumOfThreeValues::run();

  std::cout.flush();

  return 0;
}
