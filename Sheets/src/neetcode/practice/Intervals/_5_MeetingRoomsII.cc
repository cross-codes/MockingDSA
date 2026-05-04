#include "Interval.hh"
#include <algorithm>
#include <queue>
#include <vector>

class Solution
{
public:
  int minMeetingRooms(std::vector<Interval> &intervals)
  {
    if (intervals.empty())
      return 0;

    auto INTERVAL_ORDER = [](const Interval &a, const Interval &b) -> bool {
      return a.start < b.start;
    };

    std::sort(intervals.begin(), intervals.end(), INTERVAL_ORDER);
    std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
    heap.push(intervals[0].end);

    for (int i = 1; i < static_cast<int>(intervals.size()); ++i)
    {
      Interval &curr = intervals[i];

      int early_end  = heap.top();
      if (curr.start >= early_end)
      {
        heap.pop();
        heap.push(curr.end);
      }
      else
        heap.push(curr.end);
    }

    return static_cast<int>(heap.size());
  }
};
