#include <algorithm>
#include <vector>

class Solution
{
public:
  int lengthOfLIS(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());
    int len[n];
    for (int i = 0; i < n; i++)
    {
      int x = nums[i];
      int mxl{1};
      for (int j = 0; j < i; j++)
        if (nums[j] < x)
          mxl = std::max(len[j] + 1, mxl);
      len[i] = mxl;
    }

    return *std::max_element(len, len + n);
  }
};
