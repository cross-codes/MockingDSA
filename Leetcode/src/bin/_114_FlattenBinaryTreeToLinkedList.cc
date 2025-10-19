#include "TreeNode.hh"

class Solution
{
private:
  TreeNode *prev{nullptr};

  void dfs_(TreeNode *root)
  {
    if (root == nullptr)
      return;

    dfs_(root->right);
    dfs_(root->left);
    root->right = prev;
    root->left = nullptr;
    prev = root;
  }

public:
  void flatten(TreeNode *root)
  {
    dfs_(root);
  }
};
