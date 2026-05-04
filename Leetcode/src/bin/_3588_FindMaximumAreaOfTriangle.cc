#include <algorithm>
#include <climits>
#include <vector>

class Solution
{
public:
  long long maxArea(std::vector<std::vector<int>> &coords)
  {
    int n           = static_cast<int>(coords.size());

    auto PAIR_ORDER = [](const std::vector<int> &a,
                         const std::vector<int> &b) -> bool {
      int cmp = a[0] - b[0];
      if (cmp == 0)
        return a[1] < b[1];
      else
        return cmp < 0;
    };

    std::sort(coords.begin(), coords.end(), PAIR_ORDER);

    int64_t mx{-1};
    for (int i = 0; i < n; i++)
    {
      int x = coords[i][0], y = coords[i][1];
      auto it = std::upper_bound(coords.begin(), coords.end(),
                                 std::vector<int>{x, INT_MAX});
      if (it != coords.begin() && *(std::prev(it)) != coords[i])
      {
        it             = std::prev(it);
        int64_t base   = (*it)[1] - y;
        int64_t height = std::max(std::abs(x - coords.front()[0]),
                                  std::abs(x - coords.back()[0]));
        if (base * height != 0)
          mx = std::max(mx, base * height);
      }
    }

    for (auto &v : coords)
      std::reverse(v.begin(), v.end());

    std::sort(coords.begin(), coords.end(), PAIR_ORDER);

    for (int i = 0; i < n; i++)
    {
      int x = coords[i][0], y = coords[i][1];
      auto it = std::upper_bound(coords.begin(), coords.end(),
                                 std::vector<int>{x, INT_MAX});
      if (it != coords.begin() && *(std::prev(it)) != coords[i])
      {
        it             = std::prev(it);
        int64_t base   = (*it)[1] - y;
        int64_t height = std::max(std::abs(x - coords.front()[0]),
                                  std::abs(x - coords.back()[0]));
        if (base * height != 0)
          mx = std::max(mx, base * height);
      }
    }

    return mx;
  }
};
