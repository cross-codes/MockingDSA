#include <vector>

class Solution
{
public:
  bool isTrionic(std::vector<int> &nums)
  {
    auto inc = [&nums](int start, int end) -> bool {
      for (int i = start + 1; i <= end; i++)
        if (nums[i] <= nums[i - 1])
          return false;

      return true;
    };

    auto dec = [&nums](int start, int end) -> bool {
      for (int i = start + 1; i <= end; i++)
        if (nums[i] >= nums[i - 1])
          return false;

      return true;
    };

    int n = static_cast<int>(nums.size());

    for (int p = 1; p < n; p++)
      for (int q = p + 1; q < n - 1; q++)
        if (inc(0, p) && dec(p, q) && inc(q, n - 1))
          return true;

    return false;
  }
};
