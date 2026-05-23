#include <climits>
#include <vector>

class Solution
{
public:
  int minimumScore(std::vector<int> &nums, std::vector<std::vector<int>> &edges)
  {
    int n = static_cast<int>(nums.size());

    std::vector<int> adj[n];
    for (const auto &vec : edges)
    {
      int u = vec[0], v = vec[1];
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    int count[n];
    auto dfs = [&count, &adj](auto &&dfs, int u, int p) -> void {
      count[u] = 1;
      for (const int &v : adj[u])
        if (v != p)
        {
          dfs(dfs, v, u);
          count[u] += count[v];
        }
    };

    dfs(dfs, 0, -1);

    std::vector<int> e(n, -1), parent(n, -1), node_id{}, ssz{}, val{};
    auto dfs2 = [&count, &adj, &e, &parent, &ssz, &node_id, &val,
                 &nums](auto &&dfs2, int u, int p) -> void {
      e[u]      = static_cast<int>(node_id.size());
      parent[u] = p;
      node_id.push_back(u);
      ssz.push_back(count[u]);
      val.push_back(nums[u]);

      for (const int &v : adj[u])
        if (v != p)
          dfs2(dfs2, v, u);
    };

    dfs2(dfs2, 0, -1);

    int prefix[n + 1];
    prefix[0] = 0;
    for (int i = 1; i <= n; i++)
      prefix[i] = prefix[i - 1] ^ val[i - 1];

    auto query_range = [&prefix](int L, int R) -> int {
      return prefix[R] ^ prefix[L];
    };

    int E     = static_cast<int>(edges.size());

    int total = query_range(0, n);
    int gmn{INT_MAX};
    for (int i = 0; i < E; i++)
      for (int j = i + 1; j < E; j++)
      {
        int u1 = edges[i][0], v1 = edges[i][1];
        int u2 = edges[j][0], v2 = edges[j][1];

        int c1              = parent[v1] == u1 ? v1 : u1;
        int c2              = parent[v2] == u2 ? v2 : u2;

        int xor1            = query_range(e[c1], e[c1] + ssz[e[c1]]);
        int xor2            = query_range(e[c2], e[c2] + ssz[e[c2]]);

        bool c1_contains_c2 = (e[c1] <= e[c2] && e[c2] < e[c1] + ssz[e[c1]]);
        bool c2_contains_c1 = (e[c2] <= e[c1] && e[c1] < e[c2] + ssz[e[c2]]);

        int x0{}, x1{}, x2{};
        if (c1_contains_c2)
        {
          x2 = xor2;
          x1 = xor1 ^ xor2;
          x0 = total ^ xor1;
        }
        else if (c2_contains_c1)
        {
          x1 = xor1;
          x2 = xor2 ^ xor1;
          x0 = total ^ xor2;
        }
        else
        {
          x1 = xor1;
          x2 = xor2;
          x0 = total ^ x1 ^ x2;
        }

        int mx = std::max({x0, x1, x2});
        int mn = std::min({x0, x1, x2});
        gmn    = std::min(gmn, mx - mn);
      }

    return gmn;
  }
};
