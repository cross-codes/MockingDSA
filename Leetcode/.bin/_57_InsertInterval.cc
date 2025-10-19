#include <algorithm>
#include <vector>

class Solution
{
private:
  std::vector<std::vector<int>> merge(std::vector<std::vector<int>> &intervals)
  {
    int n = static_cast<int>(intervals.size());
    std::vector<std::vector<int>> res{};

    std::sort(intervals.begin(), intervals.end());
    int cur{};
    while (cur < n)
    {
      int cl = intervals[cur][0], cr = intervals[cur][1];
      if (cur == n - 1)
      {
        res.push_back({cl, cr});
        break;
      }

      int voyager{cur + 1};
      while (voyager < n)
      {
        int l = intervals[voyager][0], r = intervals[voyager][1];
        if (l > cr)
        {
          res.push_back({cl, cr});
          goto set;
        }

        if (l <= cr)
        {
          if (r < cr)
          {
            voyager += 1;
            if (voyager == n)
            {
              res.push_back({cl, cr});
              goto set;
            }
            continue;
          }
          else
          {
            cr = r;
            voyager += 1;
            if (voyager == n)
            {
              res.push_back({cl, cr});
              goto set;
            }
            continue;
          }
        }

      set:
        cur = voyager;
        break;
      }
    }

    return res;
  }

public:
  std::vector<std::vector<int>> insert(std::vector<std::vector<int>> &intervals,
                                       std::vector<int> &newInterval)
  {
    intervals.push_back(newInterval);
    return merge(intervals);
  }
};
