#include <climits>
#include <vector>

class Solution
{
public:
  int maxProfit(std::vector<int> &prices)
  {
    int n = static_cast<int>(prices.size());

    int highest[n];
    int mx{INT_MIN};
    for (int i = n - 1; i >= 0; i--)
    {
      mx         = std::max(mx, prices[i]);
      highest[i] = mx;
    }

    int best{INT_MIN};
    for (int i = 0; i < n; i++)
      best = std::max(best, highest[i] - prices[i]);

    return best;
  }
};
