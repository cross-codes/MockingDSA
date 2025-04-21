#include <climits>
#include <vector>

class Solution
{
public:
  int maxSubArray(std::vector<int> &nums)
  {
    int n{static_cast<int>(nums.size())};
    int current_sum{}, best_sum{INT_MIN};
    for (int i = 0; i < n; i++)
    {
      current_sum = std::max(current_sum + nums[i], nums[i]);
      best_sum    = std::max(best_sum, current_sum);
    }

    return best_sum;
  }
};
