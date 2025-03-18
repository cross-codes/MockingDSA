#include <climits>
#include <unordered_set>
#include <vector>

class Solution
{
public:
  int maxSum(std::vector<int> &nums)
  {
    std::unordered_set<int> seen{};
    std::size_t n{nums.size()};

    int sum{}, maxNum{INT_MIN};
    for (std::size_t i = 0UZ; i < n; i++)
    {
      maxNum = std::max(maxNum, nums[i]);

      if (nums[i] >= 0 && !seen.contains(nums[i]))
      {
        sum += nums[i];
        seen.insert(nums[i]);
      }
    }

    return (seen.size() == 0) ? maxNum : sum;
  }
};
