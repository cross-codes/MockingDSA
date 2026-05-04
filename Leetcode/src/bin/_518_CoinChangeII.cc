#include <climits>
#include <cstdint>
#include <cstring>
#include <vector>

class Solution
{
public:
  int change(int amount, std::vector<int> &coins)
  {
    int n = static_cast<int>(coins.size());
    // w[i][j] -> ways to get a sum i using first j coins only
    // w[i][j] = w[i][j - 1] + w[i - c[j]][j]
    int w[amount + 1][n + 1];
    std::memset(w, 0x00, sizeof(w));

    int64_t ULIM = static_cast<int64_t>(INT_MAX);

    for (int j = 0; j <= n; j++)
      w[0][j] = 1;

    for (int j = 1; j <= n; j++)
      for (int i = 1; i <= amount; i++)
      {
        w[i][j] = w[i][j - 1];
        if (i >= coins[j - 1])
        {
          w[i][j] = static_cast<int>(std::min(
              ULIM, static_cast<int64_t>(w[i - coins[j - 1]][j]) + w[i][j]));
        }
      }

    return w[amount][n];
  }
};
