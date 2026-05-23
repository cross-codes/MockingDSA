#include <cstring>
#include <vector>

class Solution
{
public:
  int coinChange(std::vector<int> &coins, int amount)
  {
    int mc[amount + 1];
    std::memset(mc, 0x3f, sizeof mc);
    mc[0] = 0;

    for (int i = 0; i <= amount; i++)
      for (int c : coins)
        if (i >= c)
          mc[i] = std::min(mc[i], mc[i - c] + 1);

    return mc[amount] == 0x3f3f3f3f ? -1 : mc[amount];
  }
};
