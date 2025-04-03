#include "TreeNode.hh"
#include <utility>

class Solution
{
private:
  void dfs_(TreeNode *root)
  {
    if (root == nullptr)
      return;

    std::swap(root->left, root->right);

    dfs_(root->left);
    dfs_(root->right);
  }

public:
  TreeNode *invertTree(TreeNode *root)
  {
    dfs_(root);
    return root;
  }
};
