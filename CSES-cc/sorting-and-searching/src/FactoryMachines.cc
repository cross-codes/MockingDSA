#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <numeric>
#include <string>   // IWYU pragma: keep
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _FactoryMachines {

auto run() -> void {
  int n, t;
  std::cin >> n >> t;

  std::vector<int> k(n);
  for (int i = 0; i < n; i++) {
    std::cin >> k[i];
  }

  auto pred = [&](int64_t q) -> bool {
    __int128_t tot{};
    for (int e : k) {
      tot += q / e;
    }

    return tot >= t;
  };

  int64_t L{}, R{static_cast<int64_t>(1e18) + 1};
  while (R - L > 1) {
    int64_t M         = std::midpoint(L, R);
    (pred(M) ? R : L) = M;
  }

  std::cout << R << "\n";
}

}  // namespace _FactoryMachines

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
    _FactoryMachines::run();

  std::cout.flush();

  return 0;
}
