#include <cstring>
#include <vector>

class Solution
{
public:
  int maxCoins(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    int mxc[n + 3][n + 3];
    std::memset(mxc, 0x00, sizeof mxc);

    for (int i = 2; i <= n + 1; i++)
      mxc[i][i] = nums[i - 2] * nums[i - 1] * nums[i];

    for (int len = 2; len <= n; len++)
      for (int i = 2; i + len <= n + 2; i++)
      {
        int j = i + len - 1;
        for (int k = i; k <= j; k++)
        {
          int left = mxc[i][k - 1], right = mxc[k + 1][j];
          mxc[i][j] = std::max(mxc[i][j], left + right + nums[k - 1] * nums[i - 2] * nums[j]);
        }
      }

    return mxc[2][n + 1];
  }
};
