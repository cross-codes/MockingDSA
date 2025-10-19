#include <numeric>
#include <vector>

class Solution
{
public:
  int searchInsert(std::vector<int> &nums, int target)
  {
    int n = static_cast<int>(nums.size());
    int l{-1}, r{n};
    while (r - l > 1)
    {
      int m                      = std::midpoint(l, r);
      (target < nums[m] ? r : l) = m;
    }

    if (l == -1)
      return r;
    else
      return (nums[l] == target ? l : r);
  }
};
