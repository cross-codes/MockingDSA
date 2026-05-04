#include "TreeNode.hh"
#include <climits>

class Solution
{
  auto dfs_(TreeNode *root, int min, int max)
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
    return dfs_(root, INT_MIN, INT_MAX);
  }
};
