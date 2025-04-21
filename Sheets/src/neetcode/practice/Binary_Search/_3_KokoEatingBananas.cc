#include <algorithm>
#include <cmath>
#include <vector>

class Solution
{
public:
  int minEatingSpeed(std::vector<int> &piles, int h)
  {
    int L{0}, R{*std::max_element(piles.begin(), piles.end()) + 1};

    auto predicate = [&piles, h](int rate) -> bool {
      int total_time{};
      for (const int pile : piles)
        total_time += (pile + rate - 1) / rate;

      return total_time <= h;
    };

    while (R - L > 1)
    {
      int M = L + ((R - L) >> 1);
      if (predicate(M))
        R = M;
      else
        L = M;
    }

    return R;
  }
};
