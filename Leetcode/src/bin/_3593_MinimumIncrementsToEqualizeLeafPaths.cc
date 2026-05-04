#include <algorithm>
#include <vector>

class Solution
{
public:
  int minIncrease(int n, std::vector<std::vector<int>> &edges,
                  std::vector<int> &cost)
  {
    std::vector<int> adj[n];
    for (const auto &e : edges)
    {
      int u = e[0], v = e[1];
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    int cnt{};
    auto dfs = [&adj, &cnt, &cost](auto &&dfs, int u, int p) -> int64_t {
      std::vector<int64_t> child_max_paths{};
      for (const int &v : adj[u])
        if (v != p)
        {
          int64_t child_max_path = dfs(dfs, v, u);
          child_max_paths.push_back(child_max_path);
        }

      if (child_max_paths.empty())
        return cost[u];
      else
      {
        int64_t mx =
            *std::max_element(child_max_paths.begin(), child_max_paths.end());
        for (const int64_t &s : child_max_paths)
          if (s != mx)
            cnt += 1;

        return mx + cost[u];
      }
    };

    dfs(dfs, 0, -1);
    return cnt;
  }
};
