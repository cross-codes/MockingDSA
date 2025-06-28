#include <vector>

class Solution
{
public:
  int maxProfit(std::vector<int> &prices)
  {
    int n = static_cast<int>(prices.size());

    int x[n], y[n], z[n], a[n], b[n];
    x[0] = 0, y[0] = -prices[0], z[0] = 0, a[0] = -prices[0], b[0] = 0;

    for (int i = 1; i < n; i++)
    {
      x[i] = x[i - 1];
      y[i] = std::max(x[i - 1] - prices[i], y[i - 1]);
      z[i] = std::max(y[i - 1] + prices[i], z[i - 1]);
      a[i] = std::max(z[i - 1] - prices[i], a[i - 1]);
      b[i] = std::max(a[i - 1] + prices[i], b[i - 1]);
    }

    return std::max(
        x[n - 1],
        std::max(y[n - 1], std::max(z[n - 1], std::max(a[n - 1], b[n - 1]))));
  }
};
