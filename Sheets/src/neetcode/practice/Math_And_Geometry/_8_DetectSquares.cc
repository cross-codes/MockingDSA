#include <cstdlib>
#include <set>
#include <unordered_map>
#include <vector>

class CountSquares
{
private:
  std::unordered_map<int, std::multiset<int>> x_to_y, y_to_x;

public:
  CountSquares()
  {
  }

  void add(std::vector<int> point)
  {
    x_to_y[point[0]].insert(point[1]);
    y_to_x[point[1]].insert(point[0]);
  }

  int count(std::vector<int> point)
  {
    int x1 = point[0], y1 = point[1];

    int cnt{};
    auto &x_points = y_to_x[y1];
    for (const int &x2 : x_points)
    {
      int dist = std::abs(x2 - x1);
      if (dist == 0)
        continue;

      cnt += y_to_x[y1 + dist].count(x1) * x_to_y[x2].count(y1 + dist);
      cnt += y_to_x[y1 - dist].count(x1) * x_to_y[x2].count(y1 - dist);
    }

    return cnt;
  }
};
