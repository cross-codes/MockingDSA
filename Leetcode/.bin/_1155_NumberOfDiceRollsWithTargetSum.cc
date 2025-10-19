#include <algorithm>
#include <cstdint>
#include <cstring>

class Solution
{
public:
  int numRollsToTarget(int n, int k, int target)
  {
    constexpr int MOD = static_cast<int>(1e9 + 7);

    int64_t ways[target + 1][n + 1];
    std::memset(ways, 0x00, sizeof(ways));

    ways[0][0] = 1;
    for (int m = 1; m <= n; m++)
      for (int i = 1; i <= target; i++)
      {
        for (int j = 1; j <= std::min(k, i); j++)
          ways[i][m] += ways[i - j][m - 1];

        ways[i][m] %= MOD;
      }

    return static_cast<int>(ways[target][n]);
  }
};
