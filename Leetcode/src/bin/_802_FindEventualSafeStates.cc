#include <cstring>
#include <vector>

class Solution
{
public:
  std::vector<int> eventualSafeNodes(std::vector<std::vector<int>> &adj)
  {
    int n = static_cast<int>(adj.size());
    std::vector<int> order{};

    bool visited[n];
    std::memset(visited, false, sizeof visited);
    auto dfs = [&adj, &visited, &order](auto &&dfs, int u) -> void {
      visited[u] = true;
      for (const int &v : adj[u])
        if (!visited[v])
          dfs(dfs, v);

      order.push_back(u);
    };

    for (int i = 0; i < n; i++)
      if (!visited[i])
        dfs(dfs, i);

    bool safe[n];
    std::memset(safe, false, sizeof safe);

    for (int u : order)
    {
      bool is_safe{true};
      for (const int &v : adj[u])
        if (!safe[v])
        {
          is_safe = false;
          break;
        }

      safe[u] = is_safe;
    }

    std::vector<int> res{};
    for (int i = 0; i < n; i++)
      if (safe[i])
        res.push_back(i);

    return res;
  }
};
