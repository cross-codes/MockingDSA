#include "TreeNode.hh"

class Solution
{
private:
  auto dfs_(TreeNode *p, TreeNode *q) -> bool
  {
    if (p == nullptr && q == nullptr)
      return true;

    if (p != nullptr && q != nullptr && p->val == q->val)
      return dfs_(p->left, q->left) && dfs_(p->right, q->right);
    else
      return false;
  }
public:
  bool isSameTree(TreeNode *p, TreeNode *q)
  {
    return dfs_(p, q);
  }
};
