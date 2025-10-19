#include <algorithm>
#include <array>
#include <map>
#include <vector>

class Solution
{
public:
  int minCost(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    std::map<std::pair<int, int>, int> lookup{};

    auto dfs = [&n, &nums, &lookup](auto &&dfs, int left, int pos) -> int {
      if (pos >= n)
        return left;

      if (pos == n - 1)
        return std::max(nums[pos], left);

      if (lookup.contains({left, pos}))
        return lookup[{left, pos}];

      std::array<int, 3> p = {left, nums[pos], nums[pos + 1]};
      std::sort(p.begin(), p.end());

      return lookup[{left, pos}] = std::min(p[1] + dfs(dfs, p[2], pos + 2),
                                            p[2] + dfs(dfs, p[0], pos + 2));
    };

    return dfs(dfs, nums[0], 1);
  }
};
