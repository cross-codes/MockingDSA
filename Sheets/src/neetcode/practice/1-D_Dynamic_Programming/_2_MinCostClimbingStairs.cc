#include <cstring>
#include <memory>
#include <vector>

class Solution {
public:
  int minCostClimbingStairs(std::vector<int> &cost) {
    std::size_t n = cost.size();
    std::unique_ptr<int[]> minCost(new int[n + 1]);

    std::memset(minCost.get(), 0x00, sizeof(int) * n);

    for (std::size_t i = 2; i <= n; i++)
      minCost[i] =
          std::min(cost[i - 1] + minCost[i - 1], cost[i - 2] + minCost[i - 2]);

    return minCost[n];
  }
};
