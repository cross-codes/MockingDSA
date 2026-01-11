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

namespace _CountingRooms {

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> grid(n);
  for (int y = 0; y < n; y++) {
    std::cin >> grid[y];
  }

  std::array<int, 4> dx = {-1, 0, 1, 0};
  std::array<int, 4> dy = {0, 1, 0, -1};

  auto in_bounds        = [&](int y, int x) -> bool {
    return y < n && y >= 0 && x < m && x >= 0;
  };

  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m));

  auto dfs = [&visited, &dx, &grid, &dy, &in_bounds](auto&& dfs, int y,
                                                     int x) -> void {
    visited[y][x] = true;
    for (int i = 0; i < 4; i++) {
      int X = x + dx[i], Y = y + dy[i];
      if (in_bounds(Y, X) && grid[Y][X] != '#' && !visited[Y][X]) {
        dfs(dfs, Y, X);
      }
    }
  };

  int rooms{};
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      if (grid[y][x] == '.' && !visited[y][x]) {
        rooms += 1;
        dfs(dfs, y, x);
      }
    }
  }

  std::cout << rooms << "\n";
}

}  // namespace _CountingRooms

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
    _CountingRooms::run();

  std::cout.flush();

  return 0;
}
