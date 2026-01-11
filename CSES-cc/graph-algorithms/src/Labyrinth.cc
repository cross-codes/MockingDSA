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

namespace _Labyrinth {

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<char>> grid(n, std::vector<char>(m, ' '));

  std::pair<int, int> start_pos{}, end_pos{};
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      std::cin >> grid[y][x];
      if (grid[y][x] == 'A') {
        start_pos = {y, x};
      }

      if (grid[y][x] == 'B') {
        end_pos = {y, x};
      }
    }
  }

  int dx[4] = {-1, 0, 1, 0};
  int dy[4] = {0, 1, 0, -1};

  std::vector<std::vector<std::pair<int, int>>> parents(
      n, std::vector<std::pair<int, int>>(m, {-1, -1}));

  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

  auto in_bounds = [&](int y, int x) -> bool {
    return y < n && y >= 0 && x < m && x >= 0;
  };

  bool found_path{};
  std::queue<std::pair<int, int>> queue{};
  visited[start_pos.first][start_pos.second] = true;
  queue.push(start_pos);
  while (!queue.empty()) {
    auto [y, x] = queue.front();
    queue.pop();

    if (end_pos == std::make_pair(y, x)) {
      found_path = true;
      break;
    }

    for (int i = 0; i < 4; i++) {
      int X = x + dx[i], Y = y + dy[i];
      if (in_bounds(Y, X) && grid[Y][X] != '#' && !visited[Y][X]) {
        visited[Y][X] = true;
        parents[Y][X] = {y, x};
        queue.push({Y, X});
      }
    }
  }

  auto direction_inv = [](const std::pair<int, int>& from,
                          const std::pair<int, int>& to) -> char {
    auto [y1, x1] = from;
    auto [y2, x2] = to;

    if (y1 == y2 && x1 == x2 + 1) {
      return 'R';
    } else if (y1 == y2 && x1 == x2 - 1) {
      return 'L';
    } else if (y1 == y2 + 1 && x1 == x2) {
      return 'D';
    } else {
      return 'U';
    }
  };

  if (!found_path) {
    std::cout << "NO\n";
    return;
  }

  std::string trace;
  auto curr = end_pos;
  while (parents[curr.first][curr.second] != std::make_pair(-1, -1)) {
    auto next = parents[curr.first][curr.second];
    trace.push_back(direction_inv(curr, next));
    curr = next;
  }

  std::reverse(trace.begin(), trace.end());

  std::cout << "YES " << trace.size() << "\n";
  for (char e : trace) {
    std::cout << e;
  }

  std::cout << "\n";
}

}  // namespace _Labyrinth

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
    _Labyrinth::run();

  std::cout.flush();

  return 0;
}
