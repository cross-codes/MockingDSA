#include <algorithm>
#include <vector>

/*
[[0,2],[1,4],[3,5]]
*/

class Solution
{
public:
  std::vector<std::vector<int>> merge(std::vector<std::vector<int>> &intervals)
  {
    int n = static_cast<int>(intervals.size());
    std::vector<std::vector<int>> res{};

    std::sort(intervals.begin(), intervals.end());
    for (int i = 0; i < n; i++)
    {
      if (res.empty())
        res.push_back(intervals[i]);
      else
      {
        if (intervals[i][0] <= res.back()[1])
          res.back()[1] = std::max(res.back()[1], intervals[i][1]);
        else
          res.push_back(intervals[i]);
      }
    }

    return res;
  }
};
