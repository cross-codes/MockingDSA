#include <climits>
#include <cstdint>
#include <vector>

class Solution
{
public:
  int combinationSum4(std::vector<int> &nums, int target)
  {
    // c[i] -> combinations that sum up to i
    // c[i] = sumj(c[i - a[j]])
    int c[target + 1];

    int64_t ULIM = static_cast<int64_t>(INT_MAX);

    c[0]         = 1;
    for (int i = 1; i <= target; i++)
    {
      c[i] = 0;
      for (int num : nums)
        if (num <= i)
          c[i] = static_cast<int>(
              std::min(ULIM, static_cast<int64_t>(c[i]) + c[i - num]));
    }

    return c[target];
  }
};
