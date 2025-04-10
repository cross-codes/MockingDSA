#include "TreeNode.hh"
#include <algorithm>

class Solution
{

private:
  int num_good_nodes_;

  void dfs_(TreeNode *root, int max_value)
  {
    if (root == nullptr)
      return;

    if (root->val >= max_value)
      num_good_nodes_++;

    dfs_(root->left, std::max(root->val, max_value));
    dfs_(root->right, std::max(root->val, max_value));
  }

public:
  int goodNodes(TreeNode *root)
  {
    num_good_nodes_ = 0;
    dfs_(root, root->val);
    return num_good_nodes_;
  }
};
