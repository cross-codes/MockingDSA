#include <algorithm>
#include <cstring>
#include <vector>

class Solution
{
public:
  int maxProduct(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    int mxp[n + 1], mxn[n + 1];
    std::memset(mxp, 0x00, sizeof mxp);
    std::memset(mxn, 0x00, sizeof mxn);

    bool contains_zero{};
    for (int i = 1; i <= n; i++)
    {
      int e = nums[i - 1];
      if (e > 0)
      {
        mxp[i] = std::max(mxp[i - 1] * e, e);
        mxn[i] = mxn[i - 1] * e;
      }
      else if (e < 0)
      {
        mxp[i] = std::max(mxn[i - 1] * e, 0);
        mxn[i] = std::min(mxp[i - 1] * e, e);
      }
      else
        contains_zero = true;
    }

    int res = *std::max_element(mxp, mxp + n + 1);
    if (res == 0 && !contains_zero)
      return *std::max_element(nums.begin(), nums.end());
    else
      return res;
  }
};
