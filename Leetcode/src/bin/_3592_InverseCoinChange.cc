#include <cstring>
#include <vector>

class Solution
{
public:
  std::vector<int> findCoins(std::vector<int> &numWays)
  {
    std::vector<int> coins{};

    if (numWays[0] > 1)
      return {};

    int n = static_cast<int>(numWays.size());

    for (int i = 1; i <= n; i++)
    {
      int expected = numWays[i - 1];

      int ways[i + 1];
      std::memset(ways, 0x00, sizeof(int) * (i + 1));
      ways[0] = 1;
      for (const int &c : coins)
      {
        for (int j = 0; j <= i; j++)
        {
          if (j >= c)
            ways[j] += ways[j - c];
        }
      }

      if (expected == ways[i] + 1)
        coins.push_back(i);
      else if (expected > ways[i] + 1 || expected < ways[i])
        return {};
    }

    return coins;
  }
};
