#include <algorithm>
#include <climits>
#include <queue>
#include <vector>

class Solution
{
public:
  int maxEvents(std::vector<std::vector<int>> &events)
  {
    int n = static_cast<int>(events.size());
    std::sort(events.begin(), events.end());

    int mn_start{INT_MAX}, mx_end{};
    for (int i = 0; i < n; i++)
    {
      mn_start = std::min(mn_start, events[i][0]);
      mx_end   = std::max(mx_end, events[i][1]);
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> queue;

    int mx{}, ptr{};
    for (int start = mn_start; start <= mx_end; start++)
    {
      while (ptr < n && events[ptr][0] <= start)
      {
        queue.push(events[ptr][1]);
        ptr += 1;
      }

      while (!queue.empty() && queue.top() < start)
        queue.pop();

      if (!queue.empty())
      {
        queue.pop();
        mx += 1;
      }
    }

    return mx;
  }
};
