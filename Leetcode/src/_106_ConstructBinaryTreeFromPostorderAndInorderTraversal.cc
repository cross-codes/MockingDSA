#include "TreeNode.hh"
#include <unordered_map>
#include <vector>

class Solution
{
private:
  int postorder_index_;
  std::unordered_map<int, int> inorder_key_to_index_;

  TreeNode *dfs_(const std::vector<int> &postorder, int left, int right)
  {
    if (left > right)
      return nullptr;

    int root_key   = postorder[postorder_index_--];
    TreeNode *root = new TreeNode(root_key);

    int mid        = inorder_key_to_index_[root_key];
    root->right    = dfs_(postorder, mid + 1, right);
    root->left     = dfs_(postorder, left, mid - 1);

    return root;
  }

public:
  TreeNode *buildTree(std::vector<int> &inorder, std::vector<int> &postorder)
  {
    int n = static_cast<int>(inorder.size());
    for (int i = 0; i < n; i++)
      inorder_key_to_index_[inorder[i]] = i;

    postorder_index_ = n - 1;
    return dfs_(postorder, 0, n - 1);
  }
};
