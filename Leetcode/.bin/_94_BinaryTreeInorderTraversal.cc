#include "TreeNode.hh"
#include <vector>

class Solution
{
private:
  std::vector<int> nodes_;

  void dfs_(TreeNode *root)
  {
    if (root == nullptr)
      return;

    dfs_(root->left);
    nodes_.push_back(root->val);
    dfs_(root->right);
  }

public:
  std::vector<int> inorderTraversal(TreeNode *root)
  {
    dfs_(root);
    return nodes_;
  }
};
