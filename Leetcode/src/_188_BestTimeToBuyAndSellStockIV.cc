#include <climits>
#include <cstring>
#include <vector>

class Solution
{
public:
  int maxProfit(int k, std::vector<int> &prices)
  {
    int n = static_cast<int>(prices.size());
    int fsm[(k << 1) + 1][n];
    std::memset(fsm, 0x00, sizeof(fsm));

    for (int i = 1; i < (k << 1) + 1; i += 2)
      fsm[i][0] = -prices[0];

    for (int i = 1; i < n; i++)
    {
      fsm[0][i] = fsm[0][i - 1];
      for (int j = 1; j < (k << 1) + 1; j++)
      {
        if (j & 1)
          fsm[j][i] = std::max(fsm[j - 1][i - 1] - prices[i], fsm[j][i - 1]);
        else
          fsm[j][i] = std::max(fsm[j - 1][i - 1] + prices[i], fsm[j][i - 1]);
      }
    }

    int mx{INT_MIN};
    for (int i = 0; i < (k << 1) + 1; i++)
      mx = std::max(mx, fsm[i][n - 1]);

    return mx;
  }
};
