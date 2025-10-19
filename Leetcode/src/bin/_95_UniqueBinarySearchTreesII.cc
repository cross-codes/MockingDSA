#include "TreeNode.hh"
#include <unordered_map>
#include <vector>

template <> struct std::hash<std::pair<int, int>>
{
  std::size_t operator()(const std::pair<int, int> &p) const noexcept
  {
    return (std::hash<int>{}(p.first) ^ 0x98cb78) ^ std::hash<int>{}(p.second);
  }
};

class Solution
{
public:
  std::vector<TreeNode *> generateTrees(int n)
  {
    std::unordered_map<std::pair<int, int>, std::vector<TreeNode *>> memo{};

    auto dfs = [&memo](auto &&dfs, int start,
                       int end) -> std::vector<TreeNode *> {
      std::vector<TreeNode *> res{};
      if (start > end)
      {
        res.push_back(nullptr);
        return res;
      }

      if (memo.contains({start, end}))
        return memo[{start, end}];

      for (int i = start; i <= end; i++)
      {
        std::vector<TreeNode *> left_sub_trees  = dfs(dfs, start, i - 1);
        std::vector<TreeNode *> right_sub_trees = dfs(dfs, i + 1, end);

        for (auto left : left_sub_trees)
          for (auto right : right_sub_trees)
          {
            TreeNode *root = new TreeNode(i, left, right);
            res.push_back(root);
          }
      }

      memo[{start, end}] = res;
      return res;
    };

    dfs(dfs, 1, n);
    return memo[{1, n}];
  }
};
