#include <vector>

class Solution
{
public:
  int buttonWithLongestTime(std::vector<std::vector<int>> &events)
  {
    int n = static_cast<int>(events.size());
    int best{events[0][0]}, mxt{events[0][1]};
    for (int i = 1; i < n; i++)
    {
      if (events[i][1] - events[i - 1][1] >= mxt)
      {
        if (mxt == events[i][1] - events[i - 1][1])
          best = std::min(events[i][0], best);
        else
        {
          mxt  = events[i][1] - events[i - 1][1];
          best = events[i][0];
        }
      }
    }

    return best;
  }
};
