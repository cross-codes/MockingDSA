#include <numeric>
#include <vector>

class Solution
{
public:
  int findPeakElement(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());
    if (n == 1 || nums[0] > nums[1])
      return 0;

    if (nums[n - 1] > nums[n - 2])
      return n - 1;

    auto predicate = [&nums](int m) { return nums[m] < nums[m - 1]; };

    int l{0}, r{n - 1};
    while (r - l > 1)
    {
      int m{std::midpoint(l, r)};
      (predicate(m) ? r : l) = m;
    }

    return l;
  }
};
