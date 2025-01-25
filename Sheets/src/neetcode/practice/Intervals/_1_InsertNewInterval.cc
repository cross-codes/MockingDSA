#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> insert(std::vector<std::vector<int>> &intervals,
                                       std::vector<int> &newInterval) {
    std::vector<std::vector<int>> res;
    int newStart = newInterval[0], newEnd = newInterval[1];

    size_t n = intervals.size();
    bool inserted = false;
    for (size_t i = 0; i < n; i++) {
      int curStart = intervals[i][0], curEnd = intervals[i][1];
      if (curStart > newEnd) {
        if (!inserted) {
          res.push_back(newInterval);
          inserted = true;
        }
        res.push_back(intervals[i]);
      } else if (curEnd < newStart)
        res.push_back(intervals[i]);
      else {
        newInterval[0] = std::min(newInterval[0], curStart);
        newInterval[1] = std::max(newInterval[1], curEnd);
      }
    }

    if (!inserted)
      res.push_back(newInterval);

    return res;
  }
};
