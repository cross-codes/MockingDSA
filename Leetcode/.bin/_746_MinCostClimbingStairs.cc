#include <cstring>
#include <vector>

class Solution
{
public:
  int minCostClimbingStairs(std::vector<int> &cost)
  {
    int n = static_cast<int>(cost.size());

    int min_cost[n];
    std::memset(min_cost, 0x00, sizeof(int) * n);

    for (int i = 2; i < n; i++)
      min_cost[i] = std::min(min_cost[i - 1] + cost[i - 1],
                             min_cost[i - 2] + cost[i - 2]);

    return std::min(min_cost[n - 1] + cost[n - 1],
                    min_cost[n - 2] + cost[n - 2]);
  }
};
