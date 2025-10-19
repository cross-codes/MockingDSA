#include <cstring>
#include <vector>

class Solution
{
public:
  bool canPartition(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    int tot{};
    for (int e : nums)
      tot += e;

    if (tot & 1)
      return false;
    else
    {
      int target = tot >> 1;
      bool can[target + 1][n + 1];
      std::memset(can, false, sizeof can);
      for (int i = 0; i <= n; i++)
        can[0][i] = true;

      for (int i = 0; i <= target; i++)
        for (int j = 1; j <= n; j++)
        {
          int x     = nums[j - 1];
          can[i][j] = can[i][j - 1];
          if (i >= x)
            can[i][j] |= can[i - x][j - 1];
        }

      return can[target][n];
    }
  }
};
