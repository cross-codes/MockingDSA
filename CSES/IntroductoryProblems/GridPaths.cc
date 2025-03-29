#include <bits/stdc++.h>

#if __cplusplus >= 202302L
#define dbg(a) std::println(stderr, "{}", a);
#else
#define dbg(a) std::cerr << a << "\n";
#endif

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _GridPaths {

constexpr usize N{7};

usize cnt{};
std::array<std::array<bool, N + 1>, N + 1> visited{};

enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

inline void search(usize, usize, usize, const std::string &, Direction);
inline auto inBounds(usize, usize) -> bool;
inline auto canGo(Direction, usize, usize) -> bool;

auto run() -> void {
  std::string pattern;
  std::cin >> pattern;

  search(1, 1, 0, pattern, Direction::NONE);

  std::cout << cnt << "\n";
}

inline auto inBounds(usize x, usize y) -> bool {
  return (x >= 1) && (y >= 1) && (x <= N) && (y <= N);
}

inline auto canGo(Direction dir, usize x, usize y) -> bool {
  switch (dir) {
    case Direction::UP:
      return inBounds(x, y - 1) && !visited[y - 1][x];

    case Direction::RIGHT:
      return inBounds(x + 1, y) && (!visited[y][x + 1]);

    case Direction::DOWN:
      return inBounds(x, y + 1) && !visited[y + 1][x];

    case Direction::LEFT:
      return inBounds(x - 1, y) && !visited[y][x - 1];

    default:
      return false;
  }
}

inline void search(usize x, usize y, usize idx, const std::string &pattern,
                   Direction dir) {
  if (idx == N * N - 1 || (x == 1 && y == N)) {
    if (idx == N * N - 1 && x == 1 && y == N) cnt++;

    return;
  }

  if (!canGo(dir, x, y)) {
    if (dir == Direction::UP || dir == Direction::DOWN) {
      if (canGo(Direction::RIGHT, x, y) && canGo(Direction::LEFT, x, y)) return;
    } else if (dir == Direction::RIGHT || dir == Direction::LEFT) {
      if (canGo(Direction::UP, x, y) && canGo(Direction::DOWN, x, y)) return;
    }
  }

  visited[y][x] = true;
  char c        = pattern[idx];

  if (c == 'D' || c == '?')
    if (canGo(Direction::DOWN, x, y))
      search(x, y + 1, idx + 1, pattern, Direction::DOWN);

  if (c == 'U' || c == '?')
    if (canGo(Direction::UP, x, y))
      search(x, y - 1, idx + 1, pattern, Direction::UP);

  if (c == 'R' || c == '?')
    if (canGo(Direction::RIGHT, x, y))
      search(x + 1, y, idx + 1, pattern, Direction::RIGHT);

  if (c == 'L' || c == '?')
    if (canGo(Direction::LEFT, x, y))
      search(x - 1, y, idx + 1, pattern, Direction::LEFT);

  visited[y][x] = false;
}

}  // namespace _GridPaths

int main() {
#ifdef ANTUMBRA
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
#if __cplusplus >= 202302L
    std::println(stderr, "Input file not found");
#else
    std::cerr << "Input file not found\n";
#endif
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t{1};

  while (t-- > 0) _GridPaths::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
