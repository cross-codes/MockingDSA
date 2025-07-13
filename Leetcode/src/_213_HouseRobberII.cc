#include <algorithm>
#include <cstring>
#include <vector>

class Solution
{
public:
  int rob(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    int mx1[n], mxn[n];
    std::memset(mx1, 0x00, sizeof(int) * n);
    std::memset(mxn, 0x00, sizeof(int) * n);

    mx1[0] = nums[0];
    for (int i = 1; i < n - 1; i++)
    {
      int best{};
      for (int j = 2; j <= i; j++)
        best = std::max(best, mx1[i - j]);

      mx1[i] = best + nums[i];
    }

    for (int i = 1; i < n; i++)
    {
      int best{};
      for (int j = 2; j <= i; j++)
        best = std::max(best, mxn[i - j]);

      mxn[i] = best + nums[i];
    }

    return std::max(*std::max_element(mx1, mx1 + n),
                    *std::max_element(mxn, mxn + n));
  }
};
