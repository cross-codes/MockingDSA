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

namespace _DigitQueries {

auto run() -> void {
  int64_t k;
  std::cin >> k;

  int n{1};
  int64_t sum{0}, prev_sum{0}, curr_range{9};

  while (k > sum) {
    prev_sum = sum;
    sum += n * curr_range;
    n += 1;
    curr_range *= 10;
  }

  n -= 1;
  int64_t start{static_cast<int64_t>(std::pow(INT64_C(10), n - 1))};
  int64_t skip = (k - prev_sum - 1) / n;
  int ch_skip  = (k - prev_sum - 1) % n;
  std::cout << std::to_string(start + skip)[ch_skip] << "\n";
}

}  // namespace _DigitQueries

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
  std::cin >> t;
  while (t-- > 0)
    _DigitQueries::run();

  std::cout.flush();

  return 0;
}
