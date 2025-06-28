#include <vector>

class Solution
{
public:
  int maxProfit(std::vector<int> &prices)
  {
    int n = static_cast<int>(prices.size());

    // profit at end of day i if you hold a stock / let go of a stock
    int hold[n], release[n];
    hold[0] = -prices[0], release[0] = 0;

    for (int i = 1; i < n; i++)
    {
      hold[i]    = std::max(hold[i - 1], release[i - 1] - prices[i]);
      release[i] = std::max(release[i - 1], hold[i - 1] + prices[i]);
    }

    return release[n - 1];
  }
};
