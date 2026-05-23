#include <algorithm>
#include <cstring>
#include <vector>

class Solution
{
public:
  int findNumberOfLIS(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    int l[n], cnt[n]; // length ending at i, number of ending at i
    std::memset(l, 0x00, sizeof(int) * n);
    std::fill(cnt, cnt + n, 1);

    for (int i = 0; i < n; i++)
    {
      int mx{};
      for (int j = 0; j < i; j++)
        if (nums[j] < nums[i])
        {
          if (mx < l[j] + 1)
          {
            mx     = std::max(mx, l[j] + 1);
            cnt[i] = cnt[j];
          }
          else if (mx == l[j] + 1)
            cnt[i] += cnt[j];
        }

      l[i] = std::max(mx, 1);
    }

    int mx = *std::max_element(l, l + n);
    int res{};

    for (int i = 0; i < n; i++)
      if (l[i] == mx)
        res += cnt[i];

    return res;
  }
};
