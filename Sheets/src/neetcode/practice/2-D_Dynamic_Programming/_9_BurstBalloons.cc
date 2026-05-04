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

    for (int len = 2; len < n; ++len)
      for (int l = 0, r = l + len; r < n; ++l, ++r)
      {
        int border = nums[l] * nums[r], best{};

        for (int k = l + 1; k < r; ++k)
        {
          int q = mxc[l][k] + mxc[k][r] + border * nums[k];
          if (q > best)
            best = q;
        }

        mxc[l][r] = best;
      }

    return mxc[0][n - 1];
  }
};
