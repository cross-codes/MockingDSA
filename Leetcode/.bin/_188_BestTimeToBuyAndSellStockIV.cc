#include <climits>
#include <vector>

class Solution
{
public:
  int maxProfit(int k, std::vector<int> &prices)
  {
    int n = static_cast<int>(prices.size());

    int fsm[(k << 1) + 1][n + 1];
    for (int i = 0; i < (k << 1) + 1; i++)
      fsm[i][0] = (i & 1) ? INT_MIN : 0;

    for (int i = 1; i <= n; i++)
    {
      fsm[0][i] = fsm[0][i - 1];

      for (int j = 1; j < (k << 1); j++)
        if (j & 1)
          fsm[j][i] =
              std::max(fsm[j][i - 1], fsm[j - 1][i - 1] - prices[i - 1]);
        else
          fsm[j][i] =
              std::max(fsm[j][i - 1], fsm[j - 1][i - 1] + prices[i - 1]);

      fsm[k << 1][i] = std::max(fsm[k << 1][i - 1],
                                fsm[(k << 1) - 1][i - 1] + prices[i - 1]);
    }

    int mx{};
    for (int i = 0; i < (k << 1) + 1; i++)
      mx = std::max(mx, fsm[i][n]);

    return mx;
  }
};
