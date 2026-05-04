#include <cstring>
#include <vector>

class Solution
{
public:
  int maxProfit(std::vector<int> &prices)
  {
    int n = static_cast<int>(prices.size());

    int profit[n][2];
    for (int i = 0; i < n; i++)
      std::memset(profit[i], 0x00, sizeof(int) * 2);

    auto dfs = [&profit, &n, &prices](auto &&dfs, int idx, int can_buy) -> int {
      if (idx >= n)
        return 0;

      if (profit[idx][can_buy])
        return profit[idx][can_buy];

      int cooldown = dfs(dfs, idx + 1, can_buy);
      if (can_buy)
      {
        int buy              = dfs(dfs, idx + 1, can_buy ^ 1) - prices[idx];
        profit[idx][can_buy] = std::max(cooldown, buy);
      }
      else
      {
        int sell             = dfs(dfs, idx + 2, can_buy ^ 1) + prices[idx];
        profit[idx][can_buy] = std::max(cooldown, sell);
      }

      return profit[idx][can_buy];
    };

    return dfs(dfs, 0, 1);
  }
};
