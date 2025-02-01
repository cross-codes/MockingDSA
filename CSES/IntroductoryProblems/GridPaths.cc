#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 7;

size_t cnt = 0;
bool visited[_ + 1][_ + 1];

enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

void search(size_t, size_t, size_t, std::string, Direction);
auto inBounds(size_t x, size_t y) -> bool;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string pattern;
  std::cin >> pattern;

  search(1, 1, 0, pattern, Direction::NONE);

  std::cout << cnt << "\n";

  return 0;
}

auto inBounds(size_t x, size_t y) -> bool {
  return (x >= 1) && (y >= 1) && (x <= _) && (y <= _);
}

void search(size_t x, size_t y, size_t idx, std::string pattern,
            Direction dir) {
  if (idx == _ * _ - 1 || (x == 1 && y == _)) {
    if (idx == _ * _ - 1 && x == 1 && y == _)
      cnt++;

    return;
  }


  if (dir == Direction::UP) {
    if (!inBounds(x, y - 1) || visited[y - 1][x])
      if (inBounds(x - 1, y) && !visited[y][x - 1] && inBounds(x + 1, y) &&
          !visited[y][x + 1])
        return;
  } else if (dir == Direction::DOWN) {
    if (!inBounds(x, y + 1) || visited[y + 1][x])
      if (inBounds(x - 1, y) && !visited[y][x - 1] && inBounds(x + 1, y) &&
          !visited[y][x + 1])
        return;
  } else if (dir == Direction::RIGHT) {
    if (!inBounds(x + 1, y) || visited[y][x + 1])
      if (inBounds(x, y - 1) && !visited[y - 1][x] && inBounds(x, y + 1) &&
          !visited[y + 1][x])
        return;
  } else if (dir == Direction::LEFT) {
    if (!inBounds(x - 1, y) || visited[y][x - 1])
      if (inBounds(x, y + 1) && !visited[y + 1][x] && inBounds(x, y - 1) &&
          !visited[y - 1][x])
        return;
  }

  visited[y][x] = true;
  char c = pattern[idx];

  if (c == '?') {
    if (inBounds(x, y + 1) && !visited[y + 1][x])
      search(x, y + 1, idx + 1, pattern, Direction::DOWN);

    if (inBounds(x, y - 1) && !visited[y - 1][x])
      search(x, y - 1, idx + 1, pattern, Direction::UP);

    if (inBounds(x + 1, y) && !visited[y][x + 1])
      search(x + 1, y, idx + 1, pattern, Direction::RIGHT);

    if (inBounds(x - 1, y) && !visited[y][x - 1])
      search(x - 1, y, idx + 1, pattern, Direction::LEFT);

  } else if (c == 'D') {
    if (inBounds(x, y + 1) && !visited[y + 1][x])
      search(x, y + 1, idx + 1, pattern, Direction::DOWN);
  } else if (c == 'U') {
    if (inBounds(x, y - 1) && !visited[y - 1][x])
      search(x, y - 1, idx + 1, pattern, Direction::UP);
  } else if (c == 'R') {
    if (inBounds(x + 1, y) && !visited[y][x + 1])
      search(x + 1, y, idx + 1, pattern, Direction::RIGHT);
  } else {
    if (inBounds(x - 1, y) && !visited[y][x - 1])
      search(x - 1, y, idx + 1, pattern, Direction::LEFT);
  }

  visited[y][x] = false;
}
