#include <cassert>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <vector>

class Solution
{
public:
  std::vector<int> findMedian(int n, std::vector<std::vector<int>> &edges,
                              std::vector<std::vector<int>> &queries)
  {

    std::vector<std::pair<int, int>> adj[n];
    for (const auto &v : edges)
    {
      int a = v[0], b = v[1], c = v[2];
      adj[a].emplace_back(b, c);
      adj[b].emplace_back(a, c);
    }

    int succ[n][20];
    for (int i = 0; i < 20; i++)
      succ[0][i] = -1;

    int64_t esum[n];
    int depth[n];
    esum[0] = 0, depth[0] = 0;

    auto dfs = [&succ, &adj, &esum, &depth](auto &&dfs, int u, int p) -> void {
      for (const auto &[v, w] : adj[u])
        if (v != p)
        {
          esum[v]    = w + esum[u];
          depth[v]   = 1 + depth[u];
          succ[v][0] = u;
          dfs(dfs, v, u);
        }
    };

    dfs(dfs, 0, -1);

    for (int i = 1; i < 20; i++)
      for (int u = 0; u < n; u++)
        if (succ[u][i - 1] == -1)
          succ[u][i] = -1;
        else
          succ[u][i] = succ[succ[u][i - 1]][i - 1];

    auto ancestor = [&succ](int u, int k) -> int {
      int curr{u};
      while (k != 0)
      {
        int pos = __builtin_ctz(k);
        curr    = succ[curr][pos];
        if (curr == -1)
          return -1;
        k &= (k - 1);
      }

      return curr;
    };

    auto LCA = [&succ, &ancestor, &depth](int u, int v) -> int {
      if (depth[u] < depth[v])
        std::swap(u, v);

      u = ancestor(u, depth[u] - depth[v]);

      if (u == v)
        return u;

      for (int i = 19; i >= 0; i--)
        if (succ[u][i] != succ[v][i])
        {
          u = succ[u][i];
          v = succ[v][i];
        }

      return succ[u][0];
    };

    std::vector<int> res{};
    for (const auto &q : queries)
    {
      int u = q[0], v = q[1];
      if (u == v)
      {
        res.push_back(u);
        continue;
      }

      int l = LCA(u, v);

      if (l == -1)
        l = (depth[u] < depth[v]) ? u : v;

      int64_t total = esum[u] + esum[v] - (esum[l] << 1);

      // sum from u to x is >= target
      auto predu = [&u, &esum, &total, &ancestor](int x) -> bool {
        return esum[u] - esum[ancestor(u, x)] >=
               static_cast<int64_t>(std::ceil(total / 2.0L));
      };

      int L{-1}, R{depth[u] - depth[l] + 1};
      while (R - L > 1)
      {
        int M              = std::midpoint(L, R);
        (predu(M) ? R : L) = M;
      }

      if (R != depth[u] - depth[l] + 1)
        res.push_back(ancestor(u, R));
      else
      {
        // sum from u to x is < target
        auto predv = [&u, &v, &esum, &l, &total, &ancestor](int x) -> bool {
          return esum[u] + esum[ancestor(v, x)] - (esum[l] << 1) <
                 static_cast<int64_t>(std::ceil(total / 2.0L));
        };

        L = -1, R = depth[v] - depth[l];
        while (R - L > 1)
        {
          int M              = std::midpoint(L, R);
          (predv(M) ? R : L) = M;
        }

        res.push_back(ancestor(v, L));
      }
    }

    return res;
  }
};
