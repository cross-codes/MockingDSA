#include <climits>
#include <cstring>
#include <numeric>
#include <vector>

class Solution
{
public:
  int minTime(int n, std::vector<std::vector<int>> &edges, int k)
  {
    auto dfs = [](auto &&dfs, int u, std::vector<int> adj[],
                  bool visited[]) -> void {
      visited[u] = true;

      for (const auto &v : adj[u])
        if (!visited[v])
          dfs(dfs, v, adj, visited);
    };

    // dcc >= k;
    auto pred = [&n, &edges, &dfs, &k](int t) -> bool {
      std::vector<int> adj[n];

      for (const auto &vec : edges)
      {
        int u = vec[0], v = vec[1], time = vec[2];
        if (time > t)
        {
          adj[u].push_back(v);
          adj[v].push_back(u);
        }
      }

      bool visited[n];
      std::memset(visited, false, sizeof(bool) * n);

      int dcc{};
      for (int i = 0; i < n; i++)
      {
        if (!visited[i])
        {
          dcc += 1;
          dfs(dfs, i, adj, visited);
        }
      }

      return dcc >= k;
    };

    int mxtime{INT_MIN};
    for (const auto &vec : edges)
      mxtime = std::max(mxtime, vec[2]);

    if (mxtime == INT_MIN)
      return 0;

    int L{-1}, R{mxtime + 1};
    while (R - L > 1)
    {
      int M             = std::midpoint(L, R);
      (pred(M) ? R : L) = M;
    }

    return R;
  }
};
