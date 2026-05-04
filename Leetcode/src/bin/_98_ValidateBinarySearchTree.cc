#include "TreeNode.hh"
#include <climits>
#include <cstdint>

class Solution
{
  auto dfs_(TreeNode *root, int64_t min, int64_t max) -> bool
  {
    if (root == nullptr)
      return true;

    if (root->val <= min || root->val >= max)
      return false;

    return dfs_(root->left, min, root->val) &&
           dfs_(root->right, root->val, max);
  }

public:
  bool isValidBST(TreeNode *root)
  {
    return dfs_(root, INT64_MIN, INT64_MAX);
  }
};
