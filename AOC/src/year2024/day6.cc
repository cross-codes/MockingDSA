#include "../include/io.hpp"
#include <vector>

IO io;

#define cin ::io
#define cout ::io

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

namespace part1 {

i64 simulateGrid(std::vector<std::vector<char>>, int, int, Direction);
Direction rotateClockwise(Direction);

void run() {
  int caretRow = -1, caretColumn = -1;
  Direction direction = Direction::NONE;

  std::vector<std::vector<char>> map{};
  do {
    std::string input;
    cin >> input;
    std::vector<char> rowList{};

    for (char c : input) {
      rowList.push_back(c);

      switch (c) {
      case '^':
        caretRow = map.size();
        caretColumn = rowList.size() - 1;
        direction = Direction::UP;
        break;

      case '>':
        caretRow = map.size();
        caretColumn = rowList.size() - 1;
        direction = Direction::RIGHT;
        break;

      case '<':
        caretRow = map.size();
        caretColumn = rowList.size() - 1;
        direction = Direction::LEFT;
        break;

      case 'v':
        caretRow = map.size();
        caretColumn = rowList.size() - 1;
        direction = Direction::DOWN;
        break;

      default:
        break;
      }
    }

    map.push_back(rowList);
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  i64 distinct = simulateGrid(map, caretRow, caretColumn, direction);
  cout << distinct << "\n";
}

i64 simulateGrid(std::vector<std::vector<char>> grid, int crow, int ccol,
                 Direction direction) {
  int rows = grid.size(), cols = grid[0].size();
  int i = crow, j = ccol;

  i64 result = 0LL;
  while (true) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
      break;
    }

    switch (direction) {
    case Direction::UP:
      if (grid[i][j] == '.' || grid[i][j] == '^') {
        grid[i][j] = 'X';
        result++;
        i--;
      } else if (grid[i][j] == 'X') {
        i--;
      } else {
        i++;
        direction = rotateClockwise(direction);
      }

      break;

    case Direction::DOWN:
      if (grid[i][j] == '.' || grid[i][j] == 'v') {
        grid[i][j] = 'X';
        result++;
        i++;
      } else if (grid[i][j] == 'X') {
        i++;
      } else {
        i--;
        direction = rotateClockwise(direction);
      }

      break;

    case Direction::LEFT:
      if (grid[i][j] == '.' || grid[i][j] == '<') {
        grid[i][j] = 'X';
        result++;
        j--;
      } else if (grid[i][j] == 'X') {
        j--;
      } else {
        j++;
        direction = rotateClockwise(direction);
      }

      break;

    case Direction::RIGHT:
      if (grid[i][j] == '.' || grid[i][j] == '>') {
        grid[i][j] = 'X';
        result++;
        j++;
      } else if (grid[i][j] == 'X') {
        j++;
      } else {
        j--;
        direction = rotateClockwise(direction);
      }

      break;

    default:
      throw direction;
    }
  }

  return result;
}

Direction rotateClockwise(Direction currentDirection) {
  switch (currentDirection) {
  case Direction::UP:
    return Direction::RIGHT;

  case Direction::RIGHT:
    return Direction::DOWN;

  case Direction::DOWN:
    return Direction::LEFT;

  case Direction::LEFT:
    return Direction::UP;

  default:
    return Direction::NONE;
  }
}

} // namespace part1

namespace part2 {
void run() {}
} // namespace part2

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Invalid args\n";
  } else if (strcmp(argv[1], "1") == 0) {
    part1::run();
  } else if (strcmp(argv[1], "2") == 0) {
    part2::run();
  } else {
    cout << "Invalid args\n";
  }
  return 0;
}
