#include <algorithm>
#include <cstring>
#include <vector>

class Solution
{
public:
  int rob(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    int max[n];
    std::memset(max, 0x00, sizeof(int) * n);

    max[0] = nums[0];

    for (int i = 1; i < n; i++)
    {
      int best{};
      for (int j = 2; j <= i; j++)
        best = std::max(best, max[i - j]);

      max[i] = best + nums[i];
    }

    return *std::max_element(max, max + n);
  }
};
