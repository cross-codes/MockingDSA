#include <algorithm>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> combinationSum2(std::vector<int> &candidates,
                                                int target)
  {
    std::sort(candidates.begin(), candidates.end());
    int n{static_cast<int>(candidates.size())};
    std::vector<std::vector<int>> res{};

    auto dfs = [&candidates, &target, &n, &res](auto &&dfs,
                                                std::vector<int> &subset,
                                                int idx, int acc) -> void {
      if (acc == target)
      {
        res.push_back(subset);
        return;
      }

      if (idx >= n || acc > target)
        return;

      for (int i = idx; i < n; i++)
      {
        if (i > idx && candidates[i] == candidates[i - 1])
          continue;

        subset.push_back(candidates[i]);
        dfs(dfs, subset, i + 1, acc + candidates[i]);
        subset.pop_back();
      }
    };

    std::vector<int> subset{};
    dfs(dfs, subset, 0, 0);
    return res;
  }
};
