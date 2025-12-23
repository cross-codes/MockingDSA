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

namespace _MaximumSubarraySum {

auto run() -> void {
  int n;
  std::cin >> n;

  int64_t cur{}, mx{INT64_MIN}, mxe{INT64_MIN};
  bool all_neg{true};
  for (int64_t i = 0, x; i < n; i++) {
    std::cin >> x;
    all_neg = all_neg && x < 0;
    mxe     = std::max(mxe, x);
    cur     = std::max(INT64_C(0), x + cur);
    mx      = std::max(mx, cur);
  }

  std::cout << (all_neg ? mxe : mx) << "\n";
}

}  // namespace _MaximumSubarraySum

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
    _MaximumSubarraySum::run();

  std::cout.flush();

  return 0;
}
