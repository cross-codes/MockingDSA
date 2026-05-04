#include <algorithm>
#include <climits>
#include <vector>

class Solution
{
public:
  int threeSumClosest(std::vector<int> &nums, int target)
  {
    int n = static_cast<int>(nums.size());
    std::sort(nums.begin(), nums.end());

    int mn_diff{INT_MAX}, best{};
    for (int i = 0; i < n; i++)
    {
      int l{i + 1}, r{n - 1};
      while (l < r)
      {
        int nsum{nums[l] + nums[r]};
        int absdiff = std::abs(target - (nsum + nums[i]));

        if (absdiff < mn_diff)
        {
          mn_diff = absdiff;
          best    = nsum + nums[i];
        }

        if (nsum + nums[i] < target)
          l += 1;
        else if (nsum + nums[i] > target)
          r -= 1;
        else
          return nsum + nums[i];
      }
    }

    return best;
  }
};
