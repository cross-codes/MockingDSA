#include <climits>
#include <cstring>
#include <vector>

class Solution
{
private:
  struct Info
  {
    int node_id;
    int subtree_size;
    int path_cost;
  };

public:
  int minIncrease(int n, std::vector<std::vector<int>> &edges,
                  std::vector<int> &cost)
  {
    std::vector<int> adj[n];
    for (const auto &edge : edges)
    {
      adj[edge[0]].push_back(edge[1]);
      adj[edge[1]].push_back(edge[0]);
    }

    bool visited[n];
    std::memset(visited, false, sizeof(bool) * n);

    std::vector<Info> tt{};

    auto dfs = [&visited, &adj, &tt, &cost](auto &&dfs, int u,
                                            int path_cost) -> int {
      visited[u]         = true;
      int curr_path_cost = path_cost + cost[u];

      int subtree_size{1};
      tt.emplace_back(u, subtree_size, curr_path_cost);
      int idx = static_cast<int>(tt.size() - 1);

      for (int v : adj[u])
      {
        if (!visited[v])
          subtree_size += dfs(dfs, v, curr_path_cost);
      }

      tt[idx].subtree_size = subtree_size;
      return subtree_size;
    };

    dfs(dfs, 0, 0);

    int max_sum{INT_MIN};
    for (const auto &data : tt)
    {
      if (data.subtree_size == 1)
        max_sum = std::max(max_sum, data.path_cost);
    }

    int updates{};
    for (int i = 1; i < n; i++)
    {
      const Info &e = tt[i];
      int size      = e.subtree_size;

      int max_cost{INT_MIN};
      int num_max{}, num_leaves{};
      for (int j = i; j < i + size; j++)
      {
        const Info &f = tt[j];
        if (f.path_cost > max_cost)
        {
          num_max  = 1;
          max_cost = f.path_cost;
        }
        else if (f.path_cost == max_cost)
          num_max += 1;

        if (f.subtree_size == 1)
          num_leaves += 1;
      }

      if (max_cost == max_sum)
        updates += num_leaves - num_max;
      else
      {
        if (size == 1)
          updates += 1;
        else
          updates += size - num_max;
      }

      i += size - 1;
    }

    return updates;
  }
};
