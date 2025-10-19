#include <algorithm>
#include <vector>

class Solution
{
public:
  int eraseOverlapIntervals(std::vector<std::vector<int>> &intervals)
  {
    auto INTERVAL_ORDER = [](const std::vector<int> &a,
                             const std::vector<int> &b) -> bool {
      return a[1] < b[1];
    };

    std::sort(intervals.begin(), intervals.end(), INTERVAL_ORDER);
    int n = static_cast<int>(intervals.size());

    int cnt{};
    int prevr{-50001};
    for (int i = 0; i < n; i++)
    {
      int l = intervals[i][0], r = intervals[i][1];
      if (l < prevr)
      {
        cnt += 1;
        continue;
      }
      prevr = r;
    }

    return cnt;
  }
};
