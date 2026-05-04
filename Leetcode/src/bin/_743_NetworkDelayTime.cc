#include <climits>
#include <cstring>
#include <queue>
#include <vector>

class Solution
{
public:
  int networkDelayTime(std::vector<std::vector<int>> &times, int n, int k)
  {
    std::vector<std::pair<int, int>> adj[n];
    for (const auto &vec : times)
    {
      int a = vec[0], b = vec[1], c = vec[2];
      adj[a - 1].emplace_back(b - 1, c);
    }

    int distance[n];
    std::memset(distance, 0x3f, sizeof(int) * n);

    bool processed[n];
    std::memset(processed, false, sizeof(bool) * n);

    distance[k - 1] = 0;
    std::priority_queue<std::pair<int, int>> heap{};
    heap.emplace(0, k - 1);

    while (!heap.empty())
    {
      int a = heap.top().second;
      heap.pop();

      if (processed[a])
        continue;

      processed[a] = true;
      for (const auto &[b, w] : adj[a])
      {
        if (distance[a] + w < distance[b])
        {
          distance[b] = distance[a] + w;
          heap.emplace(-distance[b], b);
        }
      }
    }

    int mx{INT_MIN};
    for (int e : distance)
      mx = std::max(mx, e);

    return mx == 0x3f3f3f3f ? -1 : mx;
  }
};
