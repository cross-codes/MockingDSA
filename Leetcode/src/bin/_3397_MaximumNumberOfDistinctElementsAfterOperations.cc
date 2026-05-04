#include <algorithm>
#include <climits>
#include <vector>

class Solution
{
public:
  int maxDistinctElements(std::vector<int> &nums, int k)
  {
    std::sort(nums.begin(), nums.end());
    int curr{INT_MIN}, cnt{};
    for (int num : nums)
    {
      int curmx = std::max(curr, num - k);
      if (curmx <= num + k)
      {
        curr = curmx + 1;
        cnt += 1;
      }
    }

    return cnt;
  }
};
