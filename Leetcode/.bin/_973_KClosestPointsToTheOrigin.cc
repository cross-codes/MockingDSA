#include <algorithm>
#include <cstdint>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> &points,
                                         int k)
  {
    auto distance = [](const std::vector<int> &a) -> int64_t {
      return a[0] * a[0] + a[1] * a[1];
    };

    auto PAIR_ORDER = [&distance](const std::vector<int> &a,
                                  const std::vector<int> &b) -> bool {
      return distance(a) < distance(b);
    };

    std::sort(points.begin(), points.end(), PAIR_ORDER);
    std::vector<std::vector<int>> res(k);
    for (int i = 0; i < k; i++)
      res[i] = std::move(points[i]);

    return res;
  }
};
