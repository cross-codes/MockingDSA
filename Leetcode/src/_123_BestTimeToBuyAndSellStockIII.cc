#include <climits>
#include <vector>

class Solution
{
public:
  int maxProfit(std::vector<int> &prices)
  {
    int n = static_cast<int>(prices.size());

    int free_2[n + 1], hold_1[n + 1], free_1[n + 1], hold_2[n + 1],
        free_0[n + 1];
    free_2[0] = free_1[0] = free_0[0] = 0;
    hold_1[0] = hold_2[0] = INT_MIN;

    for (int i = 1; i <= n; i++)
    {
      free_2[i] = free_2[i - 1];
      hold_1[i] = std::max(hold_1[i - 1], free_2[i - 1] - prices[i - 1]);
      free_1[i] = std::max(free_1[i - 1], hold_1[i - 1] + prices[i - 1]);
      hold_2[i] = std::max(hold_2[i - 1], free_1[i - 1] - prices[i - 1]);
      free_0[i] = std::max(free_0[i - 1], hold_2[i - 1] + prices[i - 1]);
    }

    return std::max({free_2[n], hold_1[n], free_1[n], hold_2[n], free_0[n]});
  }
};
