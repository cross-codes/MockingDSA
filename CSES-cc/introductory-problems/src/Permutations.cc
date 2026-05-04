#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <utility>    // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _Permutations {

auto run() -> void {
  int n;
  std::cin >> n;

  if (n == 2 || n == 3) [[unlikely]] {
    std::cout << "NO SOLUTION\n";
    return;
  }

  if (n & 1) {
    for (int i = 2; i <= n - 1; i += 2) {
      std::cout << i << " ";
    }
    for (int i = 1; i <= n; i += 2) {
      std::cout << i << " ";
    }
  } else {
    for (int i = 2; i <= n; i += 2) {
      std::cout << i << " ";
    }
    for (int i = 1; i <= n - 1; i += 2) {
      std::cout << i << " ";
    }
  }

  std::cout << "\n";
}

}  // namespace _Permutations

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
    _Permutations::run();

  std::cout.flush();

  return 0;
}
