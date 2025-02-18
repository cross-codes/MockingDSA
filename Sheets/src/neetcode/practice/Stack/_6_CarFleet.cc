#include <algorithm>
#include <climits>
#include <vector>

class Solution {
public:
  inline double time(std::pair<int, int> car, int target) {
    return (target - car.first) / static_cast<double>((car.second));
  }

  int carFleet(int target, std::vector<int> &position,
               std::vector<int> &speed) {
    std::size_t n = position.size();
    std::vector<std::pair<int, int>> cars(n);

    for (std::size_t i = 0; i < n; i++)
      cars[i] = {position[i], speed[i]};

    std::sort(cars.begin(), cars.end(), std::greater<std::pair<int, int>>());

    double maxTime = -1e9;
    int cnt = 0;
    for (const auto &pair : cars) {
      double time = this->time(pair, target);
      if (time > maxTime) {
        maxTime = time;
        cnt++;
      }
    }

    return cnt;
  }
};
