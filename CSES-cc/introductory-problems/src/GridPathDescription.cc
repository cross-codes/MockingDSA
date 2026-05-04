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

namespace _GridPathDescription {

constexpr int N{7};
std::array<std::array<bool, N + 1>, N + 1> visited{};

enum Direction { UP, DOWN, LEFT, RIGHT, NONE };

auto run() -> void {
  std::string s;
  std::cin >> s;

  auto in_bounds = [](int y, int x) -> bool {
    return x >= 1 && y >= 1 && x <= N && y <= N;
  };

  auto can_go = [in_bounds](Direction dir, int y, int x) -> bool {
    switch (dir) {
      case UP:
        return in_bounds(y - 1, x) && !visited[y - 1][x];

      case RIGHT:
        return in_bounds(y, x + 1) && !visited[y][x + 1];

      case DOWN:
        return in_bounds(y + 1, x) && !visited[y + 1][x];

      case LEFT:
        return in_bounds(y, x - 1) && !visited[y][x - 1];

      default:
        return false;
    }
  };

  int cnt{};
  auto search = [&s, &cnt, can_go](auto&& search, int y, int x, Direction dir,
                                   int idx) -> void {
    if (idx == N * N - 1 || (x == 1 && y == N)) {
      if (idx == N * N - 1 && x == 1 && y == N) {
        cnt += 1;
      }

      return;
    }

    if (!can_go(dir, y, x)) {
      if (dir == Direction::UP || dir == Direction::DOWN) {
        if (can_go(Direction::RIGHT, y, x) && can_go(Direction::LEFT, y, x)) {
          return;
        }
      } else if (dir == Direction::RIGHT || dir == Direction::LEFT) {
        if (can_go(Direction::UP, y, x) && can_go(Direction::DOWN, y, x)) {
          return;
        }
      }
    }

    visited[y][x] = true;
    char c        = s[idx];

    if (c == 'D' || c == '?') {
      if (can_go(Direction::DOWN, y, x)) {
        search(search, y + 1, x, Direction::DOWN, idx + 1);
      }
    }

    if (c == 'U' || c == '?') {
      if (can_go(Direction::UP, y, x)) {
        search(search, y - 1, x, Direction::UP, idx + 1);
      }
    }

    if (c == 'R' || c == '?') {
      if (can_go(Direction::RIGHT, y, x)) {
        search(search, y, x + 1, Direction::RIGHT, idx + 1);
      }
    }

    if (c == 'L' || c == '?') {
      if (can_go(Direction::LEFT, y, x)) {
        search(search, y, x - 1, Direction::LEFT, idx + 1);
      }
    }

    visited[y][x] = false;
  };

  search(search, 1, 1, Direction::NONE, 0);
  std::cout << cnt << "\n";
}

}  // namespace _GridPathDescription

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
    _GridPathDescription::run();

  std::cout.flush();

  return 0;
}
