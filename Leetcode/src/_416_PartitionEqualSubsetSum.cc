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

    bool possible[n + 1][target + 1]; // possible[i][sum] create sum using [0..i];
    for (int i = 0; i <= n; i++)
      std::memset(possible[i], false, sizeof(bool) * (target + 1));

    for (int i = 0; i <= n; i++)
      possible[i][0] = true;

    for (int i = 1; i <= n; i++)
      for (int j = 0; j <= target; j++)
      {
        if (nums[i - 1] <= j)
          possible[i][j] =
              possible[i - 1][j] || possible[i - 1][j - nums[i - 1]];
        else
          possible[i][j] = possible[i - 1][j];
      }

    return possible[n][target];
  }
};
