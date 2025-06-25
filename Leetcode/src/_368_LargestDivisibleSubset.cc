#include <algorithm>
#include <cstring>
#include <vector>

class Solution
{
public:
  std::vector<int> largestDivisibleSubset(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    std::ranges::sort(nums);

    int l[n], p[n];
    std::memset(l, 0x00, sizeof(int) * n);
    std::memset(p, -1, sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
      int mx{};
      for (int j = 0; j < i; j++)
        if (nums[i] % nums[j] == 0)
        {
          if (l[j] + 1 > mx)
          {
            mx   = l[j] + 1;
            p[i] = j;
          }
        }

      l[i] = std::max(mx, 1);
    }

    auto idx = std::distance(l, std::max_element(l, l + n));

    std::vector<int> subset{};
    while (idx != -1)
    {
      subset.push_back(nums[idx]);
      idx = p[idx];
    }

    return subset;
  }
};
