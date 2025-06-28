#include <climits>
#include <cstring>
#include <vector>

class Solution
{
public:
  int coinChange(std::vector<int> &coins, int amount)
  {
    int req[amount + 1]; // req[i] -> min coins to make i
    std::memset(req, 0x00, sizeof(int) * (amount + 1));

    for (int i = 1; i <= amount; i++)
    {
      req[i] = INT_MAX;
      for (int c: coins)
        if (i >= c && req[i - c] >= 0)
          req[i] = std::min(req[i], req[i - c] + 1);

      if (req[i] == INT_MAX)
        req[i] = -1;
    }

    return req[amount];
  }
};
