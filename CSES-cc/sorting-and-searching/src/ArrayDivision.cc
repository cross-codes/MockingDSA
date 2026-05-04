#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <deque>      // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <numeric>
#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <utility>        // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _ArrayDivision {

auto run() -> void {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> x(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
  }

  auto pred = [&](int64_t q) -> bool {
    int cnt{1};
    int64_t cur{};
    for (int e : x) {
      if (cur + e > q) {
        cnt += 1;
        cur = e;
      } else {
        cur += e;
      }
    }

    return cnt <= k;
  };

  int64_t L{*std::max_element(x.begin(), x.end()) - 1},
      R{((((int64_t)(1e14)) << 1) + 1)};

  while (R - L > 1) {
    int64_t M         = std::midpoint(L, R);
    (pred(M) ? R : L) = M;
  }

  std::cout << R << "\n";
}

}  // namespace _ArrayDivision

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
    _ArrayDivision::run();

  std::cout.flush();

  return 0;
}
