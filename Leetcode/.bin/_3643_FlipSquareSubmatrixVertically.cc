#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> reverseSubmatrix(
      std::vector<std::vector<int>> &grid, int x, int y, int k)
  {
    for (int i = 0; i < k / 2; i++)
    {
      std::swap_ranges(std::next(grid[x + i].begin(), y),
                       std::next(std::next(grid[x + i].begin(), y), k),
                       std::next(grid[x + k - 1 - i].begin(), y));
    }

    return grid;
  }
};
