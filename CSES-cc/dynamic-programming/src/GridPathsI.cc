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

namespace _GridPathsI {

constexpr int MOD = 1000000007;

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<std::vector<char>> grid(n + 1, std::vector<char>(n + 1, '$'));
  for (int y = 1; y <= n; y++) {
    for (int x = 1; x <= n; x++) {
      std::cin >> grid[y][x];
    }
  }

  std::vector<std::vector<int>> ways(n + 1, std::vector<int>(n + 1, 0));
  ways[1][1] = (grid[1][1] == '*') ? 0 : 1;
  for (int y = 1; y <= n; y++) {
    for (int x = 1; x <= n; x++) {
      if (grid[y][x] != '*') {
        ways[y][x] += (grid[y - 1][x] != '*') ? ways[y - 1][x] : 0;
        ways[y][x] += (grid[y][x - 1] != '*') ? ways[y][x - 1] : 0;
        ways[y][x] %= MOD;
      }
    }
  }

  std::cout << ways[n][n] << "\n";
}

}  // namespace _GridPathsI

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
    _GridPathsI::run();

  std::cout.flush();

  return 0;
}
