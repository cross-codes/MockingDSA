#include <vector>

class Solution
{
public:
  int minTaps(int n, std::vector<int> &ranges)
  {
    std::vector<int> arr(n + 1, 0);
    for (int i = 0; i <= n; ++i)
    {
      if (ranges[i] == 0)
        continue;
      int left  = std::max(0, i - ranges[i]);
      arr[left] = std::max(arr[left], i + ranges[i]);
    }

    int end = 0, far_can_reach = 0, cnt = 0;
    for (int i = 0; i <= n; ++i)
    {
      if (i > end)
      {
        if (far_can_reach <= end)
          return -1;
        end = far_can_reach;
        cnt += 1;
      }
      far_can_reach = std::max(far_can_reach, arr[i]);
    }

    return cnt + (end < n);
  }
};
