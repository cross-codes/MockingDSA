#include <algorithm>
#include <vector>

class Solution
{
public:
  int maxArea(std::vector<int> &height)
  {
    int n = static_cast<int>(height.size());
    int swl{}, l{}, r{n - 1};
    int mx = *std::max_element(height.begin(), height.end());
    int best{};
    while (l < r && swl <= mx)
    {
      while (height[l] < swl && l < r)
        l += 1;
      while (height[r] < swl && r > l)
        r -= 1;

      best = std::max(swl * (r - l), best);
      swl += 1;
    }

    return best;
  }
};
