#include <cstring>
#include <vector>

class Solution
{
public:
  int countIslands(std::vector<std::vector<int>> &grid, int k)
  {
    int n        = static_cast<int>(grid.size());
    int m        = static_cast<int>(grid[0].size());

    auto get_idx = [&m](int y, int x) -> int { return m * y + x; };

    auto valid   = [&n, &m](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < m;
    };

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    bool visited[n * m];
    std::memset(visited, false, sizeof visited);

    auto dfs = [&grid, &k, &visited, &dx, &dy, get_idx,
                &valid](auto &&dfs, int y, int x, int &rem) -> void {
      visited[get_idx(y, x)] = true;
      for (int i = 0; i < 4; i++)
      {
        int X{x + dx[i]}, Y{y + dy[i]};
        if (valid(Y, X) && !visited[get_idx(Y, X)] && grid[Y][X] > 0)
        {
          rem += grid[Y][X];
          rem %= k;
          dfs(dfs, Y, X, rem);
        }
      }
    };

    int cnt{};
    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
      {
        if (!visited[get_idx(y, x)] && grid[y][x] > 0)
        {
          int rem{grid[y][x] % k};
          dfs(dfs, y, x, rem);
          if (rem == 0)
            cnt += 1;
        }
      }

    return cnt;
  }
};
