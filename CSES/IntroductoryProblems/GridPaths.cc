#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t N = 7;

std::size_t cnt = 0;
bool visited[N + 1][N + 1];

enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

inline void search(std::size_t, std::size_t, std::size_t, const std::string &, Direction);
inline auto inBounds(std::size_t, std::size_t) -> bool;
inline auto canGo(Direction, std::size_t, std::size_t) -> bool;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string pattern;
  std::cin >> pattern;

  search(1, 1, 0, pattern, ::Direction::NONE);

  std::cout << cnt << "\n";

  return 0;
}

inline auto inBounds(std::size_t x, std::size_t y) -> bool {
  return (x >= 1) && (y >= 1) && (x <= N) && (y <= N);
}

inline auto canGo(::Direction dir, std::size_t x, std::size_t y) -> bool {
  switch (dir) {
  case ::Direction::UP:
    return ::inBounds(x, y - 1) && !::visited[y - 1][x];

  case ::Direction::RIGHT:
    return ::inBounds(x + 1, y) && (!::visited[y][x + 1]);

  case ::Direction::DOWN:
    return ::inBounds(x, y + 1) && !::visited[y + 1][x];

  case ::Direction::LEFT:
    return ::inBounds(x - 1, y) && !::visited[y][x - 1];

  default:
    return false;
  }
}

inline void search(std::size_t x, std::size_t y, std::size_t idx, const std::string &pattern,
                   ::Direction dir) {
  if (idx == N * N - 1 || (x == 1 && y == N)) {
    if (idx == N * N - 1 && x == 1 && y == N)
      ::cnt++;

    return;
  }

  if (!::canGo(dir, x, y)) {
    if (dir == ::Direction::UP || dir == ::Direction::DOWN) {
      if (::canGo(::Direction::RIGHT, x, y) && ::canGo(::Direction::LEFT, x, y))
        return;
    } else if (dir == ::Direction::RIGHT || dir == ::Direction::LEFT) {
      if (::canGo(::Direction::UP, x, y) && ::canGo(::Direction::DOWN, x, y))
        return;
    }
  }

  ::visited[y][x] = true;
  char c = pattern[idx];

  if (c == 'D' || c == '?')
    if (::canGo(::Direction::DOWN, x, y))
      search(x, y + 1, idx + 1, pattern, ::Direction::DOWN);

  if (c == 'U' || c == '?')
    if (::canGo(::Direction::UP, x, y))
      search(x, y - 1, idx + 1, pattern, Direction::UP);

  if (c == 'R' || c == '?')
    if (::canGo(::Direction::RIGHT, x, y))
      search(x + 1, y, idx + 1, pattern, ::Direction::RIGHT);

  if (c == 'L' || c == '?')
    if (::canGo(::Direction::LEFT, x, y))
      search(x - 1, y, idx + 1, pattern, ::Direction::LEFT);

  ::visited[y][x] = false;
}
