#include <cstring>
#include <numeric>
#include <vector>

class Solution
{
public:
  bool canPartitionKSubsets(std::vector<int> &nums, int k)
  {
    int sum[1 << 16];
    std::memset(sum, -1, sizeof(int) * (1 << 16));

    int n = static_cast<int>(nums.size());
    int tot = std::accumulate(nums.begin(), nums.end(), 0);
    if (tot % k != 0)
      return false;

    int t = tot / k;

    sum[0] = 0;
    for (int s = 0; s < (1 << n); s++)
    {
      if (sum[s] == -1)
        continue;

      for (int x = 0; x < n; x++)
        if ((s & (1 << x)) == 0 && sum[s] + nums[x] <= t)
          sum[s | (1 << x)] = (sum[s] + nums[x]) % t;
    }

    return sum[(1 << n) - 1] != -1;
  }
};
