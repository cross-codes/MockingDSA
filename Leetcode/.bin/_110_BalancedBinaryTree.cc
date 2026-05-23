#include "TreeNode.hh"
#include <algorithm>
#include <cstdlib>

class Solution
{
  bool balanced{true};

  int dfs_(TreeNode *root)
  {
    if (root == nullptr)
      return 0;

    int left_incl_height  = dfs_(root->left);
    int right_incl_height = dfs_(root->right);

    if (balanced)
    {
      if (std::abs(left_incl_height - right_incl_height) >= 2)
        balanced = false;
    }

    return 1 + std::max(left_incl_height, right_incl_height);
  }

public:
  bool isBalanced(TreeNode *root)
  {
    dfs_(root);
    return balanced;
  }
};
