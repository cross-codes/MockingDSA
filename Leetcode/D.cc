#include <set>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  int countTrapezoids(std::vector<std::vector<int>> &points)
  {
    const long double PINF = 1e18;
    const long double NINF = -1e18;

    int n                  = static_cast<int>(points.size());
    std::unordered_map<long double, int> slope{};
    std::unordered_map<long double, std::set<std::pair<int, int>>> seen{};

    for (int i = 0; i < n; i++)
    {
      std::pair<int, int> p1 = {points[i][0], points[i][1]};
      for (int j = i + 1; j < n; j++)
      {
        std::pair<int, int> p2 = {points[j][0], points[j][1]};
        if (p2.first == p1.first)
        {
        }
        else
        {
          auto slope = static_cast<long double>(p2.second - p1.second) /
                       (p2.first - p1.first);
          auto &set = seen[slope];
          if (!set.contains(p1) && !set.contains(p2))
          {
          }
        }
      }
    }
  }
};
