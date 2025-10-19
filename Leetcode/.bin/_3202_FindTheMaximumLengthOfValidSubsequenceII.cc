#include <cstring>
#include <vector>

class Solution
{
public:
  int maximumLength(std::vector<int> &nums, int k)
  {
    int n = static_cast<int>(nums.size());
    for (int i = 0; i < n; i++)
      nums[i] %= k;

    int l[k][k];
    std::memset(l, 0x00, sizeof l);

    int gmx{};
    for (int r = 0; r < k; r++)
      for (int i = 0; i < n; i++)
      {
        l[nums[i]][r] = l[(r - nums[i] + k) % k][r] + 1;
        gmx           = std::max(gmx, l[nums[i]][r]);
      }

    return gmx;
  }
};
