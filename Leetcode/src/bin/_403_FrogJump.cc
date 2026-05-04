#include <array>
#include <map>
#include <vector>

class Solution
{
public:
  bool canCross(std::vector<int> &stones)
  {
    int n = static_cast<int>(stones.size());

    std::map<std::array<int, 2>, bool> lookup{};
    auto dfs = [&n, &stones, &lookup](auto &&dfs, int pos, int k) -> bool {
      if (pos == n - 1)
        return true;

      std::array<int, 2> params = {pos, k};
      if (lookup.contains(params))
        return lookup[params];

      for (int i = pos + 1; i < n; i++)
      {
        if (stones[i] - stones[pos] > k + 1)
          break;

        if (stones[i] - stones[pos] == k)
          lookup[params] = lookup[params] || dfs(dfs, i, k);

        if (pos != 0)
        {
          if (stones[i] - stones[pos] == k - 1)
            lookup[params] = lookup[params] || dfs(dfs, i, k - 1);

          if (stones[i] - stones[pos] == k + 1)
            lookup[params] = lookup[params] || dfs(dfs, i, k + 1);
        }
      }

      return lookup[params];
    };

    return dfs(dfs, 0, 1);
  }
};
