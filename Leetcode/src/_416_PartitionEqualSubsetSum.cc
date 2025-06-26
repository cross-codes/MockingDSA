#include <cstring>
#include <numeric>
#include <vector>

class Solution
{
public:
  bool canPartition(std::vector<int> &nums)
  {
    int n   = static_cast<int>(nums.size());
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0)
      return false;

    int target = sum >> 1;

    bool f[target + 1];
    std::memset(f, false, sizeof(bool) * (target + 1));
    f[0] = true;

    for (int i = 1; i <= n; i++)
      for (int j = target; j >= nums[i - 1]; j--)
        f[j] = f[j] | f[j - nums[i - 1]];

    return f[target];
  }
};
