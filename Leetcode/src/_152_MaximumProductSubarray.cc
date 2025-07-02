#include <climits>
#include <vector>

class Solution
{
public:
  int maxProduct(std::vector<int> &nums)
  {
    int res{INT_MIN}, px{1}, nx{1};
    for (int e : nums)
    {
      int temp = px * e;

      px       = std::max(temp, std::max(nx * e, e));
      nx       = std::min(temp, std::min(nx * e, e));
      res      = std::max(res, px);
    }

    return res;
  }
};
