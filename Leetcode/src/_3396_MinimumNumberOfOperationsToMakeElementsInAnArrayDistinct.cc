#include <cmath>
#include <unordered_set>
#include <vector>

class Solution
{
public:
  int minimumOperations(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    std::unordered_set<int> seen{};
    int pos{-1};
    for (int i = n - 1; i >= 0; i--)
    {
      if (seen.contains(nums[i]))
      {
        pos = i;
        break;
      }

      seen.insert(nums[i]);
    }

    if (pos == -1)
      return 0;
    else
      return static_cast<int>(std::ceil((pos + 1) / 3.00));
  }
};
