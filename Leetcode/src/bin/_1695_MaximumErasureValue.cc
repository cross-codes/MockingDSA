#include <unordered_map>
#include <vector>

class Solution
{
public:
  int maximumUniqueSubarray(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    std::unordered_map<int, int> idx{};
    int l{}, r{}, mx{}, csum{};
    while (r < n)
    {
      if (!idx.contains(nums[r]))
      {
        csum += nums[r];
        mx           = std::max(csum, mx);
        idx[nums[r]] = r;
      }
      else
      {
        int pos = idx[nums[r]];
        while (l <= pos)
        {
          csum -= nums[l];
          idx.erase(nums[l]);
          l += 1;
        }
        csum += nums[r];
        mx           = std::max(csum, mx);
        idx[nums[r]] = r;
      }

      r += 1;
    }

    return mx;
  }
};
