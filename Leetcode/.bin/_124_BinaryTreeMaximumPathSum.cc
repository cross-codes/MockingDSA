#include "TreeNode.hh"
#include <algorithm>
#include <climits>

class Solution
{
private:
  int max_sum_;

  int dfs_(TreeNode *root)
  {
    if (root == nullptr)
      return 0;

    int L    = std::max(dfs_(root->left), 0);
    int R    = std::max(dfs_(root->right), 0);

    max_sum_ = std::max(max_sum_, root->val + L + R);
    return std::max(root->val + L, root->val + R);
  }

public:
  int maxPathSum(TreeNode *root)
  {
    max_sum_ = INT_MIN;
    dfs_(root);
    return max_sum_;
  }
};
