#include <cstdlib>
#include <cstring>
#include <numeric>
#include <vector>

class Solution
{
public:
  int findTargetSumWays(std::vector<int> &nums, int target)
  {
    int n   = static_cast<int>(nums.size());
    int sum = std::accumulate(nums.begin(), nums.end(), 0);

    if (sum < std::abs(target) || (sum + target) & 1)
      return 0;

    int wt = (sum + target) >> 1;
    int f[wt + 1];
    std::memset(f, 0x00, sizeof(int) * (wt + 1));

    f[0] = 1;
    for (int i = 1; i <= n; i++)
      for (int j = wt; j >= nums[i - 1]; j--)
        f[j] = f[j - nums[i - 1]] + f[j];

    return f[wt];
  }
};
