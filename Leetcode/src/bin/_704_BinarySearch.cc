#include <numeric>
#include <vector>

class Solution
{
public:
  int search(std::vector<int> &nums, int target)
  {
    int L{-1}, R{static_cast<int>(nums.size())};
    while (R - L > 1)
    {
      int M = std::midpoint(L, R);
      if (target < nums[M])
        R = M;
      else
        L = M;
    }

    if (L == -1)
      return -1;

    return nums[L] == target ? L : -1;
  }
};
