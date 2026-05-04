#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates,
                                               int target)
  {
    int n{static_cast<int>(candidates.size())};
    std::vector<std::vector<int>> res{};

    auto dfs = [&res, &target, &n,
                &candidates](auto &&dfs, int acc, int idx,
                             std::vector<int> &subset) -> void {
      if (acc > target || idx > n)
        return;

      if (acc == target)
      {
        res.push_back(subset);
        return;
      }

      for (int i = idx; i < n; i++)
      {
        subset.push_back(candidates[i]);
        dfs(dfs, acc + candidates[i], i, subset);
        subset.pop_back();
      }
    };

    std::vector<int> subset;
    dfs(dfs, 0, 0, subset);
    return res;
  }
};
