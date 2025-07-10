#include <cstring>
#include <vector>

class Solution
{
public:
  int maxFreeTime(int eventTime, std::vector<int> &startTime,
                  std::vector<int> &endTime)
  {
    int n = static_cast<int>(startTime.size());

    bool q[n];
    std::memset(q, false, sizeof(bool) * n);

    int t1{}, t2{};
    for (int i = 0; i < n; i++)
    {
      if (endTime[i] - startTime[i] <= t1)
        q[i] = true;

      t1 = std::max(t1, startTime[i] - (i == 0 ? 0 : endTime[i - 1]));

      if (endTime[n - i - 1] - startTime[n - i - 1] <= t2)
        q[n - i - 1] = true;

      t2 = std::max(t2, (i == 0 ? eventTime : startTime[n - i]) -
                            endTime[n - i - 1]);
    }

    int res{};
    for (int i = 0; i < n; i++)
    {
      int l{}, r{eventTime};
      if (i != 0)
        l = endTime[i - 1];

      if (i != n - 1)
        r = startTime[i + 1];

      if (q[i])
        res = std::max(res, r - l);
      else
        res = std::max(res, r - l - (endTime[i] - startTime[i]));
    }
    return res;
  }
};
