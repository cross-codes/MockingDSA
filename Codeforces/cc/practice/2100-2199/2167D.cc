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

namespace _2167D {

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<int64_t> a(n);
  int64_t gcd = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    gcd = std::gcd(gcd, a[i]);
  }

  if (gcd & 1) {
    std::cout << "2\n";
  } else {
    std::array<int, 17> primes = {2,  3,  5,  7,  11, 13, 17, 19, 23,
                                  29, 31, 37, 41, 43, 47, 53, 59};
    int minp                   = 59;
    for (int64_t e : a) {
      for (int p : primes) {
        if (e % p != 0) {
          minp = std::min(minp, p);
        }
      }
    }
    std::cout << minp << "\n";
  }
}

}  // namespace _2167D

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
    _2167D::run();

  std::cout.flush();

  return 0;
}
