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

namespace _DiceCombinations {

constexpr int MOD = 1000000007;

auto run() -> void {
  int n;
  std::cin >> n;

  std::array<int64_t, 1000001> ways{};
  ways[0] = 1;
  ways[1] = 1;
  ways[2] = ways[1] + ways[0];
  ways[3] = ways[2] + ways[1] + ways[0];
  ways[4] = ways[3] + ways[2] + ways[1] + ways[0];
  ways[5] = ways[4] + ways[3] + ways[2] + ways[1] + ways[0];

  for (int i = 6; i <= n; i++) {
    ways[i] = ways[i - 1] + ways[i - 2] + ways[i - 3] + ways[i - 4] +
              ways[i - 5] + ways[i - 6];
    ways[i] %= MOD;
  }

  std::cout << ways[n] << "\n";
}

}  // namespace _DiceCombinations

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
    _DiceCombinations::run();

  std::cout.flush();

  return 0;
}
