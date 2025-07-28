#include <algorithm>
#include <vector>

class Solution
{
public:
  int maxSum(std::vector<int> &nums)
  {
    std::sort(nums.begin(), nums.end());
    auto last = std::unique(nums.begin(), nums.end());
    nums.erase(last, nums.end());

    int res{};
    for (int e : nums)
      if (e > 0)
        res += e;

    if (res == 0)
      return *std::max_element(nums.begin(), nums.end());

    return res;
  }
};
