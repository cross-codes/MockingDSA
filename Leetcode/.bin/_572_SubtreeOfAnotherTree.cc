#include "TreeNode.hh"
#include <vector>

class Solution
{
private:
  auto sub_present(std::vector<std::pair<int, bool>> &sub_vec,
                   std::vector<std::pair<int, bool>> &vec, std::size_t start,
                   std::size_t length) -> bool
  {
    for (std::size_t i = start; i < start + length; i++)
      if ((sub_vec[i - start].first != vec[i].first) ||
          (sub_vec[i - start].second != vec[i].second))
        return false;

    return true;
  }

  void dfs_(std::vector<std::pair<int, bool>> &vec, TreeNode *root)
  {
    if (root == nullptr)
    {
      vec.emplace_back(-1001, true);
      return;
    }

    vec.emplace_back(root->val, false);

    dfs_(vec, root->left);
    dfs_(vec, root->right);
  }

public:
  bool isSubtree(TreeNode *root, TreeNode *sub_root)
  {
    std::vector<std::pair<int, bool>> root_vec, sub_root_vec;
    dfs_(root_vec, root);
    dfs_(sub_root_vec, sub_root);

    std::size_t n = root_vec.size(), k = sub_root_vec.size();

    if (n < k)
      return false;

    for (std::size_t i = 0; i <= n - k; i++)
    {
      if (sub_present(sub_root_vec, root_vec, i, k))
        return true;
    }

    return false;
  }
};
