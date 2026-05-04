#include <cstdint>
#include <vector>

class Solution
{
public:
  int64_t maximumScoreAfterOperations(std::vector<std::vector<int>> &edges,
                                      std::vector<int> &values)
  {
    int n = static_cast<int>(values.size());
    std::vector<int> adj[n];
    for (const auto &e : edges)
    {
      int u = e[0], v = e[1];
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    int64_t count[n];
    auto dfs = [&adj, &count, &values](auto &&dfs, int u, int p) -> void {
      count[u] = values[u];
      for (const int &v : adj[u])
        if (v != p)
        {
          dfs(dfs, v, u);
          count[u] += count[v];
        }
    };

    dfs(dfs, 0, -1);

    auto dfs2 = [&adj, &count, &values](auto &&dfs2, int u, int p) -> int64_t {
      if (adj[u].size() == 1 && adj[u][0] == p)
        return 0L;

      int64_t take = values[u];
      for (const int &v : adj[u])
        if (v != p)
          take += dfs2(dfs2, v, u);

      int64_t keep{};
      for (const int &v : adj[u])
        if (v != p)
          keep += count[v];

      return std::max(keep, take);
    };

    return dfs2(dfs2, 0, -1);
  }
};
