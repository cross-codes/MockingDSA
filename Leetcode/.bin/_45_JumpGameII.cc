#include <vector>

class Solution
{
public:
  int jump(std::vector<int> &nums)
  {
    int l{}, r{}, n{static_cast<int>(nums.size())};

    int steps{};
    while (l < n - 1 && r < n - 1)
    {
      int farthest_idx{};
      for (int i = l; i <= r; i++)
        farthest_idx = std::max(i + nums[i], farthest_idx);

      l = r + 1;
      r = farthest_idx;
      steps++;
    }

    return steps;
  }
};
