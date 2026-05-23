#include <algorithm>
#include <cstring>
#include <vector>

class Solution
{
public:
  int longestIncreasingPath(std::vector<std::vector<int>> &matrix)
  {
    int n        = static_cast<int>(matrix.size());
    int m        = static_cast<int>(matrix[0].size());

    auto get_idx = [&m](int y, int x) -> int { return (y * m) + x; };

    auto valid   = [&n, &m](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < m;
    };

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    std::vector<int> adj[m * n];

    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
        for (int i = 0; i < 4; i++)
        {
          int X{x + dx[i]}, Y{y + dy[i]};
          if (valid(Y, X) && matrix[Y][X] > matrix[y][x])
            adj[get_idx(y, x)].push_back(get_idx(Y, X));
        }

    std::vector<int> order{};

    bool visited[m * n];
    std::memset(visited, false, sizeof(bool) * m * n);
    auto dfs = [&visited, &adj, &order](auto &&dfs, int u) -> void {
      visited[u] = true;

      for (const auto &v : adj[u])
        if (!visited[v])
          dfs(dfs, v);

      order.push_back(u);
    };

    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
      {
        int idx = get_idx(y, x);
        if (!visited[idx])
          dfs(dfs, idx);
      }

    std::reverse(order.begin(), order.end());
    int tpz = static_cast<int>(order.size());

    int l[m * n];
    std::memset(l, 0x00, sizeof(int) * n * m);

    for (int i = 0; i < tpz; i++)
    {
      int u = order[i];
      for (const auto &v : adj[u])
        l[v] = std::max(l[v], l[u] + 1);
    }

    return 1 + *std::max_element(l, l + (m * n));
  }
};
