#include "Interval.hh"
#include <algorithm>
#include <vector>

class Solution
{
public:
  bool canAttendMeetings(std::vector<Interval> &intervals)
  {
    auto INTERVAL_ORDER = [](const Interval &a, const Interval &b) -> bool {
      return a.start < b.start;
    };

    int n = static_cast<int>(intervals.size());

    std::sort(intervals.begin(), intervals.end(), INTERVAL_ORDER);
    for (int i = 0; i < n - 1; i++)
    {
      if (intervals[i].end > intervals[i + 1].start)
        return false;
    }

    return true;
  }
};
