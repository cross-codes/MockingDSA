#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

class Solution
{
public:
  int minEatingSpeed(std::vector<int> &piles, int h)
  {
    int64_t L{0}, R{*std::max_element(piles.begin(), piles.end()) + 1};

    auto predicate = [&piles, h](int64_t rate) -> bool {
      int64_t total_time{};
      for (const int pile : piles)
        total_time += (pile + rate - 1) / rate;

      return total_time <= h;
    };

    while (R - L > 1)
    {
      int64_t M = std::midpoint(L, R);
      if (predicate(M))
        R = M;
      else
        L = M;
    }

    return static_cast<int>(R);
  }
};
