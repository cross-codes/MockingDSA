#include <algorithm>
#include <vector>

class Solution {
private:
  inline int distanceSquare(const std::vector<int> &a) {
    int x1 = a[0], x2 = a[1];
    return x1 * x1 + x2 * x2;
  }

public:
  std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> &points,
                                         int k) {
    std::size_t n = points.size();
    std::vector<std::vector<int>> res{};

    auto DISTANCE_ORDER = [this](const std::vector<int> &a,
                                 const std::vector<int> &b) -> bool {
      return distanceSquare(a) >= distanceSquare(b);
    };

    std::sort(points.begin(), points.end(), DISTANCE_ORDER);
    std::copy(points.begin() + n - k, points.end(), std::back_inserter(res));

    return res;
  }
};
