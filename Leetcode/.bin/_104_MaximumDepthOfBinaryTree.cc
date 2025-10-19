#include "TreeNode.hh"
#include <algorithm>

class Solution
{
private:
  inline int dfs_(TreeNode *root)
  {
    if (root == nullptr)
      return 0;

    return 1 + std::max(dfs_(root->left), dfs_(root->right));
  }

public:
  int maxDepth(TreeNode *root)
  {
    return dfs_(root);
  }
};
