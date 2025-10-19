#include <numeric>
#include <vector>

class Solution
{
public:
  int maxFreeTime(int eventTime, int k, std::vector<int> &startTime,
                  std::vector<int> &endTime)
  {
    int n = static_cast<int>(startTime.size());

    int gaps[n + 1];
    gaps[0] = startTime[0];

    for (int i = 1; i < n; i++)
      gaps[i] = startTime[i] - endTime[i - 1];

    gaps[n] = eventTime - endTime[n - 1];

    int l{}, r{k};
    int sum = std::accumulate(gaps, gaps + k + 1, 0);
    int mx{sum};

    while (r < n)
    {
      sum -= gaps[l];
      sum += gaps[r + 1];
      mx = std::max(mx, sum);
      l += 1;
      r += 1;
    }

    return mx;
  }
};
