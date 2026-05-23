#include <cstring>
#include <queue>
#include <vector>

class Solution
{
public:
  bool isBipartite(std::vector<std::vector<int>> &adj)
  {
    int n = static_cast<int>(adj.size());

    int colors[n], dist[n];
    std::memset(colors, -1, sizeof colors);
    std::memset(dist, 0x3f, sizeof dist);

    bool visited[n];
    std::memset(visited, false, sizeof visited);

    auto bfs = [&colors, &dist, &visited, &adj](int u) -> void {
      std::queue<int> queue{};
      dist[u] = 0;
      queue.push(u);
      visited[u] = true;

      while (!queue.empty())
      {
        int v = queue.front();
        queue.pop();

        for (const int &a : adj[v])
        {
          if (!visited[a])
          {
            visited[a] = true;
            dist[a]    = dist[v] + 1;
            colors[a]  = dist[a] & 1;
            queue.emplace(a);
          }
        }
      }
    };

    for (int i = 0; i < n; i++)
      if (!visited[i])
        bfs(i);

    std::memset(visited, false, sizeof visited);
    auto dfs = [&visited, &colors, &adj](auto &&dfs, int u, bool &bad) -> void {
      for (const int &v : adj[u])
        if (!visited[v])
        {
          if (colors[u] == colors[v])
            bad = true;

          dfs(dfs, v, bad);
        }
    };

    bool bad{};
    for (int i = 0; i < n; i++)
      if (!visited[i])
        dfs(dfs, i, bad);

    return !bad;
  }
};
