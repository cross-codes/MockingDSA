#include <unordered_map>
#include <vector>

template<> struct std::hash<std::pair<int,int>> {
  size_t operator()(const std::pair<int, int> &a) const noexcept {
    return a.first ^ 0x98be789 + (a.second << 2);
  }
};

class Solution
{
public:
  int findTargetSumWays(std::vector<int> &nums, int target)
  {
    int n = static_cast<int>(nums.size());

    std::unordered_map<std::pair<int, int>, int> ways{};
    auto dfs = [&ways, &nums, &n, &target](auto &&dfs, int idx, int acc) -> int {
      if (idx == n)
        return acc == target;

      auto it = ways.find({idx, acc});
      if (it != ways.end())
        return it->second;

      ways[{idx, acc}] = dfs(dfs, idx + 1, acc + nums[idx]) + dfs(dfs, idx + 1, acc - nums[idx]);
      return ways[{idx, acc}];
    };

    return dfs(dfs, 0, 0);
  }
};
