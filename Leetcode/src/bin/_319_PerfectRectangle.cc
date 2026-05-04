#include <climits>
#include <cstdint>
#include <set>
#include <vector>

class Solution
{
  enum EdgeType
  {
    LEFT,
    RIGHT
  };

  class RectangleEdge
  {
  public:
    std::pair<int, int> y_range;
    int64_t x;
    EdgeType type;

    RectangleEdge(int64_t x, std::pair<int, int> interval, EdgeType type)
        : y_range{interval}, x{x}, type{type}
    {
    }
  };

public:
  bool isRectangleCover(std::vector<std::vector<int>> &rectangles)
  {
    auto EDGE_ORDER = [](const RectangleEdge &a,
                         const RectangleEdge &b) -> bool {
      if (a.x == b.x)
        return a.type > b.type;
      else
        return a.x < b.x;
    };

    std::multiset<RectangleEdge, decltype(EDGE_ORDER)> edges{};

    int64_t mnx{INT_MAX}, mny{INT_MAX}, mxx{INT_MIN}, mxy{INT_MIN}, area{};
    for (const auto &r : rectangles)
    {
      int64_t x = r[0], y = r[1], a = r[2], b = r[3];
      mnx = std::min(mnx, x);
      mny = std::min(mny, y);
      mxx = std::max(mxx, a);
      mxy = std::max(mxy, b);
      area += (a - x) * (b - y);
      edges.insert(RectangleEdge(x, {y, b}, EdgeType::LEFT));
      edges.insert(RectangleEdge(a, {y, b}, EdgeType::RIGHT));
    }

    auto INTERVAL_ORDER = [](const std::pair<int, int> &a,
                             const std::pair<int, int> &b) -> bool {
      return a.first < b.first;
    };

    std::set<std::pair<int, int>, decltype(INTERVAL_ORDER)> active{};
    while (!edges.empty())
    {
      auto edge = *edges.begin();
      if (edge.type == EdgeType::LEFT)
      {
        auto it = active.lower_bound(edge.y_range);
        if (it != active.begin() && std::prev(it)->second > edge.y_range.first)
          return false;

        if (it != active.end() && it->first < edge.y_range.second)
          return false;

        active.insert(edge.y_range);
      }
      else
        active.erase(active.find(edge.y_range));

      edges.erase(edges.begin());
    }

    return area == (mxy - mny) * (mxx - mnx);
  }
};
