#include <climits>
#include <queue>
#include <vector>

class Solution
{
public:
  int maximumDifference(std::vector<int> &nums)
  {
    std::priority_queue<int, std::vector<int>, std::greater<int>> seen;
    seen.push(nums[0]);

    int max_diff{INT_MIN};
    for (const auto &e : nums)
    {
      max_diff = std::max(max_diff, e - seen.top());
      seen.push(e);
    }

    return max_diff <= 0 ? -1 : max_diff;
  }
};
