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

    int left_inclusive_height_  = dfs_(root->left);
    int right_inclusive_height_ = dfs_(root->right);

    diameter_ =
        std::max(diameter_, left_inclusive_height_ + right_inclusive_height_);

    return 1 + std::max(left_inclusive_height_, right_inclusive_height_);
  }

public:
  int diameterOfBinaryTree(TreeNode *root)
  {
    dfs_(root);
    return diameter_;
  }
};
