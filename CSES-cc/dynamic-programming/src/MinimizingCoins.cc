#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <climits>
#include <cmath>     // IWYU pragma: keep
#include <cstdint>   // IWYU pragma: keep
#include <cstring>   // IWYU pragma: keep
#include <iostream>  // IWYU pragma: keep
#include <string>    // IWYU pragma: keep
#include <utility>   // IWYU pragma: keep
#include <vector>    // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _MinimizingCoins {

auto run() -> void {
  int n, x;
  std::cin >> n >> x;

  std::vector<int> coins(n);
  for (int i = 0; i < n; i++) {
    std::cin >> coins[i];
  }

  std::array<int, 1000001> minc{};
  minc[0] = 0;
  for (int i = 1; i <= x; i++) {
    minc[i] = INT_MAX;
    for (int c : coins) {
      if (i >= c && minc[i - c] != INT_MAX) {
        minc[i] = std::min(minc[i - c] + 1, minc[i]);
      }
    }
  }

  std::cout << (minc[x] == INT_MAX ? -1 : minc[x]) << "\n";
}

}  // namespace _MinimizingCoins

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
    _MinimizingCoins::run();

  std::cout.flush();

  return 0;
}
