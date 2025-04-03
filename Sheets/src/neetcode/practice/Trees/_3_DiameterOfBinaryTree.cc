#include "TreeNode.hh"
#include <algorithm>

class Solution
{
private:
  int diameter_{};

  int dfs_(TreeNode *root)
  {
    if (root == nullptr)
      return 0;

    int left_incl_height  = dfs_(root->left);
    int right_incl_height = dfs_(root->right);

    diameter_ = std::max(diameter_, left_incl_height + right_incl_height);

    return 1 + std::max(left_incl_height, right_incl_height);
  }

public:
  int diameterOfBinaryTree(TreeNode *root)
  {
    diameter_ = 0;
    dfs_(root);
    return diameter_;
  }
};
