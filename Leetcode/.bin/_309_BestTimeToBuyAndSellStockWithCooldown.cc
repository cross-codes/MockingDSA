#include <climits>
#include <vector>

class Solution
{
public:
  int maxProfit(std::vector<int> &prices)
  {
    int n = static_cast<int>(prices.size());

    int free[n + 1], holding[n + 1], cd[n + 1];
    free[0] = cd[0] = 0;
    holding[0]      = INT_MIN;

    for (int i = 1; i <= n; i++)
    {
      free[i]    = std::max(free[i - 1], cd[i - 1]);
      holding[i] = std::max(holding[i - 1], free[i - 1] - prices[i - 1]);
      cd[i]      = holding[i - 1] + prices[i - 1];
    }

    return std::max({free[n], holding[n], cd[n]});
  }
};
