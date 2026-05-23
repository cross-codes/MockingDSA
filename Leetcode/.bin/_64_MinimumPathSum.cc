#include <cstring>
#include <vector>

class Solution
{
public:
  int minPathSum(std::vector<std::vector<int>> &grid)
  {
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());

    int mn[n][m];
    std::memset(mn, 0x3f, sizeof mn);
    mn[0][0] = grid[0][0];
    for (int x = 1; x < m; x++)
      mn[0][x] = mn[0][x - 1] + grid[0][x];

    for (int y = 1; y < n; y++)
      mn[y][0] = mn[y - 1][0] + grid[y][0];

    for (int y = 1; y < n; y++)
      for (int x = 1; x < m; x++)
        mn[y][x] =
            std::min(mn[y - 1][x] + grid[y][x], mn[y][x - 1] + grid[y][x]);

    return mn[n - 1][m - 1];
  }
};
