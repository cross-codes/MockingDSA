#include <cstring>
#include <vector>

class Solution
{
public:
  int maxCoins(std::vector<int> &nums)
  {
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    int n = static_cast<int>(nums.size());

    int mxc[n][n];
    std::memset(mxc, 0x00, sizeof(mxc));

    for (int i = 1; i < n - 1; i++)
      mxc[i][i] = nums[i - 1] * nums[i] * nums[i + 1];

    for (int len = 2; len <= n - 2; ++len)
    {
      for (int i = 1, j = i + len - 1; j < n - 1; i++, j++)
      {
        int border = nums[i - 1] * nums[j + 1], best{};
        for (int k = i; k <= j; ++k)
        {
          int q = mxc[i][k - 1] + mxc[k + 1][j] + border * nums[k];
          best  = std::max(best, q);
        }

        mxc[i][j] = best;
      }
    }

    return mxc[1][n - 2];
  }
};
