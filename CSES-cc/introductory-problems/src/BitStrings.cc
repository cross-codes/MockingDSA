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

namespace _BitStrings {

constexpr int MOD = 1000000007;

auto run() -> void {
  int n;
  std::cin >> n;

  auto mod_pow = [](int64_t x, int64_t p) -> int64_t {
    int64_t result{1};
    for (int64_t i = 1, j = x; i <= p; i <<= 1, j = j * j % MOD) {
      if (i & p) {
        result = result * j % MOD;
      }
    }

    return result;
  };

  std::cout << mod_pow(2, n) << "\n";
}

}  // namespace _BitStrings

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
    _BitStrings::run();

  std::cout.flush();

  return 0;
}
