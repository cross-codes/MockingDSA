#include "TreeNode.hh"
#include <algorithm>
#include <unordered_map>

template <> struct std::hash<std::pair<TreeNode *, bool>>
{
  size_t operator()(const std::pair<TreeNode *, bool> &a) const noexcept
  {
    return std::hash<TreeNode *>{}(a.first) ^
           0xb989c91 + std::hash<int>{}(a.second);
  };
};

class Solution
{
public:
  int rob(TreeNode *root)
  {
    std::unordered_map<std::pair<TreeNode *, bool>, int> lookup{};

    auto dfs = [&lookup](auto &&dfs, TreeNode *root, bool skip) -> int {
      if (root == nullptr)
        return 0;

      if (lookup.contains({root, skip}))
        return lookup[{root, skip}];

      if (skip)
      {
        int op1 = dfs(dfs, root->left, false) + dfs(dfs, root->right, false);
        int op2 = dfs(dfs, root->left, false) + dfs(dfs, root->right, true);
        int op3 = dfs(dfs, root->left, true) + dfs(dfs, root->right, false);
        int op4 = dfs(dfs, root->left, true) + dfs(dfs, root->right, true);
        return lookup[{root, skip}] = std::max({op1, op2, op3, op4});
      }
      else
        return lookup[{root, skip}] = root->val + dfs(dfs, root->left, true) +
                                      dfs(dfs, root->right, true);
    };

    return std::max(dfs(dfs, root, true), dfs(dfs, root, false));
  }
};
