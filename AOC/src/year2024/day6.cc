#include "../include/io.hpp"
#include <cstdint>
#include <unordered_set>
#include <vector>

IO io;

#define cin ::io
#define cout ::io

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
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

struct Collision {
  int row;
  int col;
  Direction direction;

  Collision(int row, int col, Direction direction)
      : row(row), col(col), direction(direction) {}

  struct CollisionHash {
    size_t operator()(const Collision &c) const {
      int partialHash = std::hash<int>()(c.row) ^ std::hash<int>()(c.col);
      switch (c.direction) {
      case Direction::UP:
        return partialHash ^ 20;
      case Direction::RIGHT:
        return partialHash ^ 35;
      case Direction::DOWN:
        return partialHash ^ 4;
      case Direction::LEFT:
        return partialHash ^ 9;
      case Direction::NONE:
        return partialHash ^ 0;
      }
    }
  };

  bool operator==(const Collision &c) const {
    return this->row == c.row && this->col == c.col &&
           this->direction == c.direction;
  }
};

bool causesLoop(std::vector<std::vector<char>>, int, int, int, int, Direction);
Direction rotateClockwise(Direction);

void run() {
  int caretRow = -1, caretColumn = -1;
  Direction direction = Direction::NONE;

  std::vector<std::vector<char>> grid;
  do {
    std::string row;
    cin >> row;
    std::vector<char> rowList;

    for (char c : row) {
      rowList.push_back(c);

      switch (c) {
      case '^':
        caretRow = grid.size();
        caretColumn = rowList.size() - 1;
        direction = Direction::UP;
        break;

      case '>':
        caretRow = grid.size();
        caretColumn = rowList.size() - 1;
        direction = Direction::RIGHT;
        break;

      case '<':
        caretRow = grid.size();
        caretColumn = rowList.size() - 1;
        direction = Direction::LEFT;
        break;

      case 'v':
        caretRow = grid.size();
        caretColumn = rowList.size() - 1;
        direction = Direction::DOWN;
        break;

      default:
        break;
      }
    }

    grid.push_back(rowList);
  } while (::io.input_ptr_left != ::io.input_ptr_right);

  u64 options = 0ULL;

  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] != '#' &&
          causesLoop(grid, caretRow, caretColumn, i, j, direction))
        options++;
    }
  }

  cout << options << "\n";
}

bool causesLoop(std::vector<std::vector<char>> v, int crow, int ccol, int obrow,
                int obcol, Direction direction) {
  std::unordered_set<Collision, Collision::CollisionHash> collisions{};
  if (obrow == crow && obcol == ccol)
    return false;

  v[obrow][obcol] = '#';

  int rows = v.size(), cols = v[0].size();
  int i = crow, j = ccol;

  while (true) {
    if (i < 0 || i >= rows || j < 0 || j >= cols)
      return false;

    switch (direction) {
    case Direction::UP:
      if (v[i][j] == '.' || v[i][j] == '^') {
        v[i][j] = 'X';
        i--;
      } else if (v[i][j] == 'X') {
        i--;
      } else {
        Collision collision = Collision(i, j, direction);
        if (collisions.contains(collision))
          return true;
        else
          collisions.insert(collision);
        i++;
        direction = rotateClockwise(direction);
      }
      break;

    case Direction::DOWN:
      if (v[i][j] == '.' || v[i][j] == 'v') {
        v[i][j] = 'X';
        i++;
      } else if (v[i][j] == 'X') {
        i++;
      } else {
        Collision collision = Collision(i, j, direction);
        if (collisions.contains(collision))
          return true;
        else
          collisions.insert(collision);
        i--;
        direction = rotateClockwise(direction);
      }

      break;

    case Direction::LEFT:
      if (v[i][j] == '.' || v[i][j] == '<') {
        v[i][j] = 'X';
        j--;
      } else if (v[i][j] == 'X') {
        j--;
      } else {
        Collision collision = Collision(i, j, direction);
        if (collisions.contains(collision))
          return true;
        else
          collisions.insert(collision);
        j++;
        direction = rotateClockwise(direction);
      }
      break;

    case Direction::RIGHT:
      if (v[i][j] == '.' || v[i][j] == '>') {
        v[i][j] = 'X';
        j++;
      } else if (v[i][j] == 'X') {
        j++;
      } else {
        Collision collision = Collision(i, j, direction);
        if (collisions.contains(collision))
          return true;
        else
          collisions.insert(collision);
        j--;
        direction = rotateClockwise(direction);
      }
      break;

    default:
      throw direction;
    }
  }
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
