#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <deque>
#include <iostream>  // IWYU pragma: keep
#include <string>    // IWYU pragma: keep
#include <utility>   // IWYU pragma: keep
#include <vector>    // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _NearestSmallerValues {

auto run() -> void {
  int n;
  std::cin >> n;

  std::deque<std::pair<int, int>> stack{};
  for (int i = 1, x; i <= n; i++) {
    std::cin >> x;
    while (!stack.empty() && stack.back().first >= x) {
      stack.pop_back();
    }

    std::cout << (stack.empty() ? 0 : stack.back().second) << " ";
    stack.push_back({x, i});
  }

  std::cout << "\n";
}

}  // namespace _NearestSmallerValues

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
    _NearestSmallerValues::run();

  std::cout.flush();

  return 0;
}
