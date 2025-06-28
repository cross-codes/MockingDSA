#include <climits>
#include <vector>

class Solution
{
public:
  int maxProfit(std::vector<int> &prices)
  {
    int n = static_cast<int>(prices.size());
    int free[n + 1], holding[n + 1], cd[n + 1], on_cd[n + 1];
    free[0] = 0, holding[0] = INT_MIN, cd[0] = on_cd[0] = 0;

    // free, holding, cooldown, on cooldown
    for (int i = 1; i <= n; i++)
    {
      holding[i] = std::max(holding[i - 1], free[i - 1] - prices[i - 1]);
      cd[i]      = std::max(cd[i - 1], holding[i] + prices[i - 1]);
      free[i]    = on_cd[i - 1];
      on_cd[i]   = cd[i - 1];
    }

    return std::max(free[n], std::max(holding[n], std::max(cd[n], on_cd[n])));
  }
};
