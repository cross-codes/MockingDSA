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

namespace _Monsters {

enum Character { MONSTER, PLAYER };

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
  std::queue<std::tuple<int, int, Character>> queue{};
  std::vector<std::vector<char>> grid(n, std::vector<char>(m, '#'));
  std::tuple<int, int, Character> player_params{};
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      std::cin >> grid[y][x];
      if (grid[y][x] == 'M') {
        queue.emplace(y, x, Character::MONSTER);
        visited[y][x] = true;
      } else if (grid[y][x] == 'A') {
        player_params = {y, x, Character::PLAYER};
      }
    }
  }

  auto in_bounds = [&n, &m](int y, int x) -> bool {
    return y < n && y >= 0 && x < m && x >= 0;
  };

  auto boundary = [&n, &m](int y, int x) -> bool {
    return y == n - 1 || y == 0 || x == m - 1 || x == 0;
  };

  std::array<int, 4> dx = {1, 0, -1, 0};
  std::array<int, 4> dy = {0, 1, 0, -1};

  queue.push(player_params);
  std::vector<std::vector<std::pair<int, int>>> parent(
      n, std::vector<std::pair<int, int>>(m, {-1, -1}));
  std::pair<int, int> exit = {-1, -1};
  while (!queue.empty()) {
    auto [y, x, type] = queue.front();
    queue.pop();

    if (type == Character::MONSTER) {
      for (int i = 0; i < 4; i++) {
        int X = x + dx[i], Y = y + dy[i];
        if (in_bounds(Y, X) && grid[Y][X] == '.' && !visited[Y][X]) {
          visited[Y][X] = true;
          queue.emplace(Y, X, Character::MONSTER);
        }
      }
    } else {
      if (boundary(y, x)) {
        exit = {y, x};
        goto display;
      } else {
        for (int i = 0; i < 4; i++) {
          int X = x + dx[i], Y = y + dy[i];
          if (in_bounds(Y, X) && grid[Y][X] == '.' && !visited[Y][X]) {
            visited[Y][X] = true;
            parent[Y][X]  = {y, x};
            queue.emplace(Y, X, Character::PLAYER);
          }
        }
      }
    }
  }

  std::cout << "NO\n";
  return;

display:
  std::vector<char> trace{};
  std::pair<int, int> curr = exit;

  auto direction_inv       = [](const std::pair<int, int>& from,
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

  while (!(curr.first == std::get<0>(player_params) &&
           curr.second == std::get<1>(player_params))) {
    auto next = parent[curr.first][curr.second];
    trace.push_back(direction_inv(curr, next));
    curr = next;
  }

  std::reverse(trace.begin(), trace.end());
  std::cout << "YES\n" << trace.size() << "\n";
  for (char c : trace) {
    std::cout << c;
  }

  std::cout << "\n";
}

}  // namespace _Monsters

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
    _Monsters::run();

  std::cout.flush();

  return 0;
}
