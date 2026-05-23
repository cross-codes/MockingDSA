#include <cstring>
#include <numeric>
#include <queue>
#include <vector>

class Solution
{
public:
  int maximumSafenessFactor(std::vector<std::vector<int>> &grid)
  {
    int n      = static_cast<int>(grid.size());

    auto valid = [&n](int y, int x) -> int {
      return y < n && y >= 0 && x >= 0 && x < n;
    };

    int dist[400][400];
    std::memset(dist, 0x3f, sizeof dist);

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    std::queue<std::tuple<int, int, int>> queue{};

    int mxd{};
    for (int y = 0; y < n; y++)
      for (int x = 0; x < n; x++)
      {
        if (grid[y][x] == 1)
        {
          queue.emplace(y, x, 0);
          dist[y][x] = 0;
        }
      }

    while (!queue.empty())
    {
      auto [y, x, d] = queue.front();
      queue.pop();

      for (int i = 0; i < 4; i++)
      {
        int X{x + dx[i]}, Y{y + dy[i]};
        if (valid(Y, X) && dist[Y][X] > 1 + d)
        {
          dist[Y][X] = 1 + d;
          mxd        = std::max(mxd, dist[Y][X]);
          queue.emplace(Y, X, 1 + d);
        }
      }
    }

    // 0,0 and n - 1, n - 1 are still connected on removing distv cells
    auto pred = [&dx, &dy, &dist, &valid, &n](int v) -> bool {
      if (dist[0][0] < v)
        return false;

      bool visited[400][400]{};
      std::queue<std::pair<int, int>> queue{};
      queue.emplace(0, 0);
      visited[0][0] = true;
      while (!queue.empty())
      {
        auto [y, x] = queue.front();
        queue.pop();

        if (y == n - 1 && x == n - 1)
          return true;

        for (int i = 0; i < 4; i++)
        {
          int X{x + dx[i]}, Y{y + dy[i]};
          if (valid(Y, X) && dist[Y][X] >= v && !visited[Y][X])
          {
            visited[Y][X] = true;
            queue.emplace(Y, X);
          }
        }
      }

      return false;
    };

    int L{-1}, R{mxd + 1};
    while (R - L > 1)
    {
      int M              = std::midpoint(L, R);
      (!pred(M) ? R : L) = M;
    }

    return L;
  }
};
