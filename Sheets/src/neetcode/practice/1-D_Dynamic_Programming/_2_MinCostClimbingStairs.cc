#include <cstring>
#include <vector>

class Solution {
public:
  int minCostClimbingStairs(std::vector<int> &cost) {
    size_t n = cost.size();
    int minCost[n + 1];

    std::memset(minCost, 0x00, sizeof(minCost));

    for (size_t i = 2; i <= n; i++)
      minCost[i] =
          std::min(cost[i - 1] + minCost[i - 1], cost[i - 2] + minCost[i - 2]);

    return minCost[n];
  }
};
