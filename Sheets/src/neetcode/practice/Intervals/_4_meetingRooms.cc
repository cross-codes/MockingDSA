#include "./Interval.hh"

#include <algorithm>
#include <vector>

class Solution {
public:
  inline static auto INTERVAL_ORDER = [](const Interval &a,
                                         const Interval &b) -> bool {
    int cmp = a.start - b.start;
    if (cmp == 0)
      return a.end < b.end;
    else
      return cmp < 0;
  };

  bool canAttendMeetings(std::vector<Interval> &intervals) {
    if (intervals.empty())
      return true;

    std::sort(intervals.begin(), intervals.end(), Solution::INTERVAL_ORDER);
    std::size_t n = intervals.size();

    for (std::size_t i = 0; i < n - 1; i++) {
      Interval current = intervals[i], next = intervals[i + 1];
      if (current.end > next.start)
        return false;
    }

    return true;
  }
};
