#include <cstring>
#include <queue>
#include <vector>

class Solution
{
private:
  struct Timed
  {
    int v, start, end;
    Timed() : v{-1}, start{-1}, end{-1} {};
    Timed(int v, int start, int end) : v{v}, start{start}, end{end} {};
  };

public:
  int minTime(int n, std::vector<std::vector<int>> &edges)
  {
    std::vector<Timed> adj[n];
    for (const auto &vec : edges)
    {
      int u = vec[0], v = vec[1], start = vec[2], end = vec[3];
      adj[u].emplace_back(v, start, end);
    }

    int dist[n];
    std::memset(dist, 0x3f, sizeof(int) * n);

    std::priority_queue<std::pair<int, int>> queue{};
    queue.emplace(0, 0);

    while (!queue.empty())
    {
      auto [t, a] = queue.top();
      queue.pop();

      if (-t >= dist[a])
        continue;

      dist[a] = -t;
      for (const auto &det : adj[a])
      {
        int b = det.v, s = det.start, e = det.end;
        if (-t <= e)
        {
          int tn = std::max(s, -t) + 1;
          if (tn < dist[b])
            queue.emplace(-tn, b);
        }
      }
    }

    return dist[n - 1] == 0x3f3f3f3f ? -1 : dist[n - 1];
  }
};
