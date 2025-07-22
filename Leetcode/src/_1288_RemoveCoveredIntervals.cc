#include <algorithm>
#include <vector>

class Solution
{
public:
  int removeCoveredIntervals(std::vector<std::vector<int>> &intervals)
  {
    int n           = static_cast<int>(intervals.size());
    auto SORT_ORDER = [](const std::vector<int> &a,
                         const std::vector<int> &b) -> bool {
      int cmp = a[0] - b[0];
      if (cmp == 0)
        return a[1] > b[1];
      else
        return cmp < 0;
    };

    std::sort(intervals.begin(), intervals.end(), SORT_ORDER);

    int mxr{}, cnt{};
    for (int i = 0; i < n; i++)
    {
      if (intervals[i][1] > mxr)
        mxr = intervals[i][1];
      else
        cnt += 1;
    }

    return n - cnt;
  }
};
