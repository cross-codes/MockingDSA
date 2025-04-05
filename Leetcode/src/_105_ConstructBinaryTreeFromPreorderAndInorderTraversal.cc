#include "TreeNode.hh"
#include <unordered_map>
#include <vector>

class Solution
{
private:
  int preorder_index_{};
  std::unordered_map<int, int> inorder_key_to_index_;

  TreeNode *dfs_(const std::vector<int> &preorder, int left, int right)
  {
    if (left > right)
      return nullptr;

    int root_key   = preorder[preorder_index_++];
    TreeNode *root = new TreeNode(root_key);

    int mid        = inorder_key_to_index_[root_key];
    root->left     = dfs_(preorder, left, mid - 1);
    root->right    = dfs_(preorder, mid + 1, right);

    return root;
  }

public:
  TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder)
  {
    int n = static_cast<int>(inorder.size());
    for (int i = 0; i < n; i++)
      inorder_key_to_index_[inorder[i]] = i;

    return dfs_(preorder, 0, n - 1);
  }
};
