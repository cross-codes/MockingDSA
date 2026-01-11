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
#include <queue>
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

namespace _KnightMovesGrid {

auto run() -> void {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> moves(n, std::vector<int>(n, INT_MAX));

  std::array<int, 8> dx = {-2, -1, 1, 2, -2, -1, 1, 2};
  std::array<int, 8> dy = {-1, -2, -2, -1, 1, 2, 2, 1};

  auto in_bounds        = [&n](int y, int x) -> bool {
    return y < n && y >= 0 && x < n && x >= 0;
  };

  std::queue<std::tuple<int, int, int>> queue{};
  queue.emplace(0, 0, 0);
  while (!queue.empty()) {
    auto [y, x, cnt] = queue.front();
    queue.pop();

    moves[y][x] = std::min(moves[y][x], cnt);
    for (int i = 0; i < 8; i++) {
      int Y{y + dy[i]}, X{x + dx[i]};
      if (in_bounds(Y, X) && moves[Y][X] == INT_MAX) {
        moves[Y][X] = cnt + 1;
        queue.emplace(Y, X, cnt + 1);
      }
    }
  }

  for (int y = 0; y < n; y++) {
    for (int x = 0; x < n; x++) {
      std::cout << moves[y][x] << " ";
    }
    std::cout << "\n";
  }
}

}  // namespace _KnightMovesGrid

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
    _KnightMovesGrid::run();

  std::cout.flush();

  return 0;
}
