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

namespace _Exponentiation {

constexpr int MOD = 1000000007;

auto run() -> void {
  int n;
  std::cin >> n;

  auto mod_pow = [](const int& n, const int& exponent) -> int {
    int64_t result{1};
    for (int64_t i = 1, j = n; i <= exponent; i <<= 1, j = j * j % MOD) {
      if (i & exponent) {
        result = result * j % MOD;
      }
    }

    return static_cast<int>(result);
  };

  for (int i = 0, a, b; i < n; i++) {
    std::cin >> a >> b;
    std::cout << mod_pow(a, b) << "\n";
  }
}

}  // namespace _Exponentiation

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
    _Exponentiation::run();

  std::cout.flush();

  return 0;
}
