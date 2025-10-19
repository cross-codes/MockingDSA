#include <cstring>
#include <vector>

class Solution
{
public:
  int findCircleNum(std::vector<std::vector<int>> &isConnected)
  {
    int n = static_cast<int>(isConnected.size());
    std::vector<int> adj[n];

    for (int y = 0; y < n; y++)
      for (int x = 0; x < n; x++)
        if (isConnected[y][x])
        {
          adj[y].push_back(x);
          adj[x].push_back(y);
        }

    bool visited[n];
    std::memset(visited, false, sizeof visited);
    auto dfs = [&adj, &visited](auto &&dfs, int u) -> void {
      visited[u] = true;
      for (const int &v : adj[u])
        if (!visited[v])
          dfs(dfs, v);
    };

    int cnt{};
    for (int i = 0; i < n; i++)
      if (!visited[i])
      {
        cnt += 1;
        dfs(dfs, i);
      }

    return cnt;
  }
};
