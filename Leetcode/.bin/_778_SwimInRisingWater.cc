#include <climits>
#include <cstring>
#include <numeric>
#include <vector>

class Solution
{
public:
  int swimInWater(std::vector<std::vector<int>> &grid)
  {
    int n = static_cast<int>(grid.size());
    int mn{grid[0][0]}, mx{INT_MIN};

    for (int y = 0; y < n; y++)
      for (int x = 0; x < n; x++)
        mx = std::max(mx, grid[y][x]);

    auto get_idx = [&n](int y, int x) -> int { return n * y + x; };
    auto valid   = [&n](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < n;
    };

    bool visited[n * n];

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    auto dfs  = [&visited, &valid, &dx, &dy, &grid,
                &get_idx](auto &&dfs, int y, int x, int time) -> void {
      visited[get_idx(y, x)] = true;
      for (int i = 0; i < 4; i++)
      {
        int X{x + dx[i]}, Y{y + dy[i]};
        if (valid(Y, X) && grid[Y][X] <= time && !visited[get_idx(Y, X)])
          dfs(dfs, Y, X, time);
      }
    };

    // can reach end with time
    auto pred = [&visited, &n, &dfs](int t) -> bool {
      std::memset(visited, false, sizeof(bool) * n * n);
      dfs(dfs, 0, 0, t);

      return visited[n * n - 1] == true;
    };

    int L{mn - 1}, R{mx + 1};
    while (R - L > 1)
    {
      int M             = std::midpoint(L, R);
      (pred(M) ? R : L) = M;
    }

    return R;
  }
};
