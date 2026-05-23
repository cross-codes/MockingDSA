#include <array>
#include <string>

enum class Direction { DOWN, DIAGONAL, NONE };

class Solution {
 public:
  std::string convert(std::string s, int numRows) {
    if (numRows == 1) return s;

    std::array<std::array<char, 1000>, 1000> grid{};

    std::ptrdiff_t y{}, x{};
    Direction dir = Direction::NONE;
    for (char c : s) {
      if (y == numRows - 1)
        dir = Direction::DIAGONAL;
      else if (y == 0)
        dir = Direction::DOWN;

      if (dir == Direction::DOWN)
        grid[y++][x] = c;
      else if (dir == Direction::DIAGONAL)
        grid[y--][x++] = c;
    }

    std::string res{};
    for (std::ptrdiff_t j = 0Z; j < numRows; j++)
      for (std::ptrdiff_t i = 0Z; i <= x; i++)
        if (grid[j][i] != '\0') res.push_back(grid[j][i]);

    return res;
  }
};
