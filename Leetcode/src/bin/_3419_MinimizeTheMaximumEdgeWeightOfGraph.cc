#include <algorithm>
#include <climits>
#include <cstring>
#include <numeric>
#include <vector>

class Solution
{
public:
  int minMaxWeight(int n, std::vector<std::vector<int>> &edges, int threshold)
  {
    auto WT_ORDER = [](const std::vector<int> &edge1,
                       const std::vector<int> &edge2) -> bool {
      return edge1[2] < edge2[2];
    };

    std::sort(edges.begin(), edges.end(), WT_ORDER);

    std::vector<std::pair<int, int>> adjT[n];
    int mnw{INT_MAX}, mxw{INT_MIN};
    for (const std::vector<int> &e : edges)
    {
      int u = e[0], v = e[1], w = e[2];
      adjT[v].emplace_back(u, w);
      mnw = std::min(mnw, w);
      mxw = std::max(mxw, w);
    }

    bool visited[n];
    int indegree[n];
    auto dfs = [&visited, &indegree, &adjT](auto &&dfs, int u, int k) -> void {
      visited[u] = true;
      for (const auto &[v, w] : adjT[u])
      {
        if (w > k)
          continue;
        else if (!visited[v])
        {
          indegree[v] += 1;
          dfs(dfs, v, k);
        }
      }
    };

    // all nodes can reach 0 and edge weights are < k
    auto pred = [&dfs, &visited, &indegree, &n, &threshold](int k) -> bool {
      std::memset(visited, false, sizeof visited);
      std::memset(indegree, 0x00, sizeof indegree);
      dfs(dfs, 0, k);

      bool unvisited{};
      for (int i = 0; i < n; i++)
        if (!visited[i])
        {
          unvisited = true;
          break;
        }

      bool degreesat{true};
      for (int i = 0; i < n; i++)
        if (indegree[i] > threshold)
        {
          degreesat = false;
          break;
        }

      return !unvisited && degreesat;
    };

    int L{mnw - 1}, R{mxw + 1};
    while (R - L > 1)
    {
      int M             = std::midpoint(L, R);
      (pred(M) ? R : L) = M;
    }

    if (R == mxw + 1)
      return -1;

    return R;
  }
};
