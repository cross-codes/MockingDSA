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

namespace _ChessboardAndQueens {

auto run() -> void {
  std::array<std::array<char, 8>, 8> grid{};
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      std::cin >> grid[y][x];
    }
  }

  std::array<int, 8> column{};
  std::array<int, 16> diag1{};
  std::array<int, 15> diag2{};

  int cnt{};
  auto search = [&](auto&& search, int y) {
    if (y == 8) {
      cnt += 1;
      return;
    }

    for (int x = 0; x < 8; x++) {
      if (column[x] == 1 || diag1[x + y] == 1 || diag2[x - y + 7] == 1 ||
          grid[y][x] == '*') {
        continue;
      }

      column[x] = diag1[x + y] = diag2[x - y + 7] = 1;
      search(search, y + 1);
      column[x] = diag1[x + y] = diag2[x - y + 7] = 0;
    }
  };

  search(search, 0);
  std::cout << cnt << "\n";
}

}  // namespace _ChessboardAndQueens

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
    _ChessboardAndQueens::run();

  std::cout.flush();

  return 0;
}
