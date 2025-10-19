#include "TreeNode.hh"
#include <vector>

class Solution
{
private:
  std::vector<int> right_side_;

  void dfs_(TreeNode *root, std::size_t level)
  {
    if (root == nullptr)
      return;

    if (right_side_.size() == level)
      right_side_.push_back(root->val);

    dfs_(root->right, level + 1);
    dfs_(root->left, level + 1);
  }

public:
  std::vector<int> rightSideView(TreeNode *root)
  {
    dfs_(root, 0);
    return right_side_;
  }
};
