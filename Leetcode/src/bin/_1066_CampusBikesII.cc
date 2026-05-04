#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>

class Solution
{
public:
  int iDontHaveLeetcodePremium(std::vector<std::vector<int>> &workers,
                               std::vector<std::vector<int>> &bikes)
  {
    auto dist = [](const std::vector<int> &a,
                   const std::vector<int> &b) -> int {
      return std::abs(a[0] - b[0]) + std::abs(a[1] - b[1]);
    };

    int N = static_cast<int>(workers.size());
    int M = static_cast<int>(bikes.size());

    int ways[1 << M];
    std::fill(ways, ways + (1 << M), INT_MAX);

    ways[0] = 0;
    for (int s = 0; s < (1 << M); s++)
    {
      if (ways[s] == INT_MAX)
        continue;

      int worker_idx = __builtin_popcount(s);
      if (worker_idx >= N)
        continue;

      for (int bike = 0; bike < M; bike++)
        if (!(s & (1 << bike)))
        {
          int d                 = dist(workers[worker_idx], bikes[bike]);
          ways[s | (1 << bike)] = std::min(ways[s | (1 << bike)], ways[s] + d);
        }
    }

    int result = INT_MAX;
    for (int s = 0; s < (1 << M); s++)
      if (__builtin_popcount(s) == N)
        result = std::min(result, ways[s]);

    return result;
  }
};

int main()
{
  std::vector<std::vector<int>> workers = {{0, 0}, {2, 1}};
  std::vector<std::vector<int>> bikes   = {{1, 2}, {3, 3}};

  std::cout << Solution().iDontHaveLeetcodePremium(workers, bikes);
}
