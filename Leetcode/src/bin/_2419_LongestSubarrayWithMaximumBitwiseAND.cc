#include <algorithm>
#include <vector>

class Solution
{
public:
  int longestSubarray(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    int x = *std::max_element(nums.begin(), nums.end());
    int l{}, r{}, best{};
    for (int i = 0; i < n; i++)
    {
      if (nums[i] != x)
      {
        best = std::max(best, r - l);
        l    = r + 1;
      }
      else
        best = std::max(best, r - l + 1);
      r += 1;
    }

    return best;
  }
};
