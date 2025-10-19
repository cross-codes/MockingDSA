#include <algorithm>
#include <cstring>
#include <numeric>
#include <vector>

class Solution
{
public:
  int findMaxPathScore(std::vector<std::vector<int>> &edges,
                       std::vector<bool> &online, long long k)
  {
    int n = static_cast<int>(online.size());

    std::vector<int> vertices{};
    for (int i = 0; i < n; i++)
      if (online[i])
        vertices.push_back(i);

    std::vector<std::pair<int, int>> adj[n];
    int maxw = -1;
    for (const auto &vec : edges)
    {
      int u = vec[0], v = vec[1], w = vec[2];
      if (online[u] && online[v])
      {
        adj[u].emplace_back(v, w);
        maxw = std::max(w, maxw);
      }
    }

    if (maxw == -1)
      return -1;

    bool visited[n];
    std::memset(visited, false, sizeof visited);
    std::vector<int> order{};
    auto dfs = [&visited, &order, &adj](auto &&dfs, int u) -> void {
      visited[u] = true;
      for (const auto &[v, _] : adj[u])
        if (!visited[v])
          dfs(dfs, v);
      order.push_back(u);
    };
    for (int u : vertices)
      if (!visited[u])
        dfs(dfs, u);
    std::reverse(order.begin(), order.end());

    auto pred = [&](int t) -> bool {
      int64_t sum[n];
      const int64_t INF = 0x3f3f3f3f3f3f3f3f;
      std::memset(sum, 0x3f, sizeof sum);
      sum[0] = 0;

      for (int u : order)
      {
        if (sum[u] == INF)
          continue;

        for (const auto &[v, w] : adj[u])
        {
          if (w >= t)
          {
            sum[v] = std::min(sum[v], sum[u] + w);
          }
        }
      }
      return sum[n - 1] != INF && sum[n - 1] <= k;
    };

    int L = -1, R = maxw + 1;
    while (R - L > 1)
    {
      int M = std::midpoint(L, R);

      if (pred(M))
      {
        L = M;
      }
      else
      {
        R = M;
      }
    }
    return L;
  }
};
