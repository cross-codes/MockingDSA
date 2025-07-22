#include <cstring>
#include <queue>
#include <vector>

class Solution
{
public:
  int shortestPathBinaryMatrix(std::vector<std::vector<int>> &grid)
  {
    int n = static_cast<int>(grid.size());

    if (grid[0][0] != 0)
      return -1;

    std::vector<int> adj[n * n];

    auto get_idx = [&n](int y, int x) -> int { return n * y + x; };

    auto valid   = [&n](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < n;
    };

    int dx[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
    int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};

    for (int y = 0; y < n; y++)
      for (int x = 0; x < n; x++)
      {
        if (grid[y][x] == 0)
        {
          int s = get_idx(y, x);
          for (int i = 0; i < 8; i++)
          {
            int X{x + dx[i]}, Y{y + dy[i]};
            if (valid(Y, X) && grid[Y][X] == 0)
            {
              int t = get_idx(Y, X);
              adj[s].push_back(t);
              adj[t].push_back(s);
            }
          }
        }
      }

    bool processed[n * n];
    std::memset(processed, false, sizeof processed);

    int dist1[n * n];
    std::memset(dist1, 0x3f, sizeof dist1);
    std::queue<std::pair<int, int>> queue{};
    dist1[0] = 0;
    queue.emplace(0, 0);
    while (!queue.empty())
    {
      int u = queue.front().second;
      queue.pop();

      if (processed[u])
        continue;

      processed[u] = true;
      for (const int &v : adj[u])
      {
        if (dist1[v] > dist1[u] + 1)
        {
          dist1[v] = dist1[u] + 1;
          queue.emplace(-dist1[v], v);
        }
      }
    }

    return dist1[n * n - 1] == 0x3f3f3f3f ? -1 : dist1[n * n - 1] + 1;
  }
};
