#include <algorithm>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> divideArray(std::vector<int> &nums, int k)
  {
    int n = static_cast<int>(nums.size());
    std::ranges::sort(nums);

    std::vector<std::vector<int>> res{};

    for (int i = 0; i < n - 2; i += 3)
    {
      if (nums[i + 2] - nums[i] > k)
        return {};
      else
        res.push_back({nums[i], nums[i + 1], nums[i + 2]});
    }

    return res;
  }
};
