#include <cstring>
#include <queue>
#include <vector>

class Solution
{
public:
  std::vector<bool> findAnswer(int n, std::vector<std::vector<int>> &edges)
  {
    std::vector<std::pair<int, int>> adj[n];

    for (const auto &v : edges)
    {
      int a = v[0], b = v[1], w = v[2];
      adj[a].emplace_back(b, w);
      adj[b].emplace_back(a, w);
    }

    int dist1[n], distN[n];
    std::memset(dist1, 0x3f, sizeof(int) * n);
    std::memset(distN, 0x3f, sizeof(int) * n);

    bool processed[n];
    std::memset(processed, false, sizeof(bool) * n);

    std::priority_queue<std::pair<int, int>> queue{};
    queue.emplace(0, 0);
    dist1[0] = 0;

    while (!queue.empty())
    {
      int a = queue.top().second;
      queue.pop();

      if (processed[a])
        continue;

      processed[a] = true;
      for (const auto &[b, w] : adj[a])
      {
        if (dist1[b] > dist1[a] + w)
        {
          dist1[b] = dist1[a] + w;
          queue.emplace(-dist1[b], b);
        }
      }
    }

    std::memset(processed, false, sizeof(bool) * n);
    queue.emplace(0, n - 1);
    distN[n - 1] = 0;

    while (!queue.empty())
    {
      int a = queue.top().second;
      queue.pop();

      if (processed[a])
        continue;

      processed[a] = true;
      for (const auto &[b, w] : adj[a])
      {
        if (distN[b] > distN[a] + w)
        {
          distN[b] = distN[a] + w;
          queue.emplace(-distN[b], b);
        }
      }
    }

    std::vector<bool> res(edges.size(), false);
    if (dist1[n - 1] == 0x3f3f3f3f)
      return res;

    int m = static_cast<int>(edges.size());
    for (int i = 0; i < m; i++)
    {
      int a = edges[i][0], b = edges[i][1], w = edges[i][2];
      if (dist1[a] + w + distN[b] == dist1[n - 1] ||
          dist1[b] + w + distN[a] == dist1[n - 1])
        res[i] = true;
    }

    return res;
  }
};
