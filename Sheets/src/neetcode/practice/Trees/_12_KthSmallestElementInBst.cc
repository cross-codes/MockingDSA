#include "TreeNode.hh"

class Solution
{
private:
  int counter_{};
  TreeNode *res_;

  void dfs_(TreeNode *root, int k)
  {
    if (root == nullptr)
      return;

    dfs_(root->left, k);

    counter_++;
    if (counter_ == k)
    {
      res_   = root;
      return;
    }

    dfs_(root->right, k);
  }

public:
  int kthSmallest(TreeNode *root, int k)
  {
    dfs_(root, k);
    return res_->val;
  }
};
