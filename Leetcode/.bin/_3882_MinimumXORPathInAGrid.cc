#include <algorithm>
#include <climits>
#include <vector>

class Solution
{
public:
  int minCost(std::vector<std::vector<int>> &grid)
  {
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());

    std::vector<std::vector<std::array<bool, 1024>>> visited(
        n, std::vector<std::array<bool, 1024>>(m));

    auto valid = [&](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < m;
    };

    int best = INT_MAX;
    auto dfs = [&](auto &&dfs, int y, int x, int acc) -> void {
      if (y == n - 1 && x == m - 1)
      {
        best = std::min(best, acc ^ grid[n - 1][m - 1]);
        return;
      }

      if (visited[y][x][acc])
      {
        return;
      }

      visited[y][x][acc] = true;

      int Y1{y + 1}, X1{x};
      if (valid(Y1, X1))
      {
        dfs(dfs, Y1, X1, acc ^ grid[y][x]);
      }

      int Y2{y}, X2{x + 1};
      if (valid(Y2, X2))
      {
        dfs(dfs, Y2, X2, acc ^ grid[y][x]);
      }
    };

    dfs(dfs, 0, 0, 0);
    return best;
  }
};
