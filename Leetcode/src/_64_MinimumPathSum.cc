#include <array>
#include <climits>
#include <vector>

class Solution
{
public:
  int minPathSum(std::vector<std::vector<int>> &grid)
  {
    auto m = grid.size(), n = grid[0].size();
    std::array<std::array<int, 201>, 201> minCost;

    std::fill(minCost[0].begin(), minCost[0].end(), INT_MAX);
    for (std::size_t i = 0; i < 201; i++)
      minCost[i][0] = INT_MAX;

    minCost[1][1] = grid[0][0];
    for (std::size_t y = 1UZ; y <= m; y++)
      for (std::size_t x = 1UZ; x <= n; x++)
        if (!(y == 1UZ && x == 1UZ))
          minCost[y][x] = grid[y - 1][x - 1] +
                          std::min(minCost[y - 1][x], minCost[y][x - 1]);

    return minCost[m][n];
  }
};
