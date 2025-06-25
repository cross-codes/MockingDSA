#include <vector>

class Solution
{
public:
  int findTargetSumWays(std::vector<int> &nums, int target)
  {
    int n = static_cast<int>(nums.size());

    int ways{};
    auto dfs = [&ways, &nums, &n, &target](auto &&dfs, int idx,
                                           int acc) -> void {
      if (idx == n)
      {
        if (acc == target)
          ways += 1;

        return;
      }

      dfs(dfs, idx + 1, acc - nums[idx]);
      dfs(dfs, idx + 1, acc + nums[idx]);
    };

    dfs(dfs, 0, 0);
    return ways;
  }
};
