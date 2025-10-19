#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>

class Solution
{
public:
  int maxValue(std::vector<std::vector<int>> &events, int k)
  {
    int n           = static_cast<int>(events.size());

    auto SORT_ORDER = [](const std::vector<int> &a,
                         const std::vector<int> &b) -> bool {
      return a[1] < b[1];
    };

    std::sort(events.begin(), events.end(), SORT_ORDER);

    // index of latest event compatible with events[i]
    int p[n + 1];
    std::memset(p, 0x00, sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++)
    {
      int s                         = events[i - 1][0];
      const std::vector<int> search = {0, s - 1, 0};
      auto it =
          std::upper_bound(events.begin(), events.end(), search, SORT_ORDER);

      if (it != events.begin())
      {
        it      = std::prev(it);
        int idx = static_cast<int>(std::distance(events.begin(), it));
        p[i]    = idx + 1;
      }
      else
        p[i] = 0;
    }

    // max value of j events in the first i days
    int mx[n + 1][k + 1];
    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= k; j++)
        mx[i][j] = INT_MIN;

    for (int i = 0; i <= n; i++)
      mx[i][0] = 0;

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= k; j++)
        mx[i][j] = std::max(mx[p[i]][j - 1] + events[i - 1][2], mx[i - 1][j]);

    int res{};
    for (int i = 0; i <= k; i++)
      res = std::max(res, mx[n][i]);

    return res;
  }
};
