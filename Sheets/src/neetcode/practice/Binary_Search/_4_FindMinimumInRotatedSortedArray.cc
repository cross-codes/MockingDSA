#include <vector>

class Solution
{
public:
  int findMin(std::vector<int> &nums)
  {
    int n{static_cast<int>(nums.size())};
    if (nums[0] <= nums[n - 1])
      return nums[0];

    int l{-1}, r{n};
    while (r - l > 1)
    {
      int m{l + ((r - l) >> 1)};
      ((nums[m] < nums[0]) ? r : l) = m;
    }

    return nums[r];
  }
};
