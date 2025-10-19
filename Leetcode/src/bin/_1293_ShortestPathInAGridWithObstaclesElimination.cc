#include <cstring>
#include <queue>
#include <vector>

class Solution
{
public:
  int shortestPath(std::vector<std::vector<int>> &grid, int k)
  {
    int n      = static_cast<int>(grid.size());
    int m      = static_cast<int>(grid[0].size());

    auto valid = [&n, &m](int y, int x) -> bool {
      return y < n && y >= 0 && x < m && x >= 0;
    };

    std::queue<std::tuple<int, int, int, int>> queue{}; // y, x, d, k
    queue.emplace(0, 0, 0, grid[0][0] == 1);

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    int os[n][m];
    std::memset(os, 0x3f, sizeof os);

    os[0][0] = grid[0][0] == 1;
    while (!queue.empty())
    {
      auto [y, x, d, o] = queue.front();
      queue.pop();

      if (y == n - 1 && x == m - 1 && o <= k)
        return d;

      if (o <= k)
      {
        for (int i = 0; i < 4; i++)
        {
          int X{x + dx[i]}, Y{y + dy[i]};
          if (valid(Y, X) && os[Y][X] > o + (grid[Y][X] == 1))
          {
            os[Y][X] = o + (grid[Y][X] == 1);
            queue.emplace(Y, X, 1 + d, o + (grid[Y][X] == 1));
          }
        }
      }
    }

    return -1;
  }
};
