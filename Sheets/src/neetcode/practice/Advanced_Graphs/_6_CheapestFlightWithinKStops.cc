#include <vector>
#include <cstring>

class Solution
{
public:
  int findCheapestPrice(int n, std::vector<std::vector<int>> &flights, int src,
                        int dst, int k)
  {
    int dist[n], temp[n];
    std::memset(dist, 0x3f, sizeof(int) * n);

    dist[src] = 0;

    for (int i = 0; i <= k; i++)
    {
      std::memcpy(temp, dist, n * sizeof(int));
      for (const auto &vec : flights)
      {
        int a = vec[0], b = vec[1], w = vec[2];
        temp[b] = std::min(temp[b], dist[a] + w);
      }
      std::memcpy(dist, temp, n * sizeof(int));
    }

    return dist[dst] == 0x3f3f3f3f ? -1 : dist[dst];
  }
};
