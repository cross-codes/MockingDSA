#include "TreeNode.hh"
#include <array>
#include <climits>
#include <vector>

class Solution
{
private:
  std::array<TreeNode *, 1001> vertices_{};
  std::vector<std::pair<int, int>> tt_{}; // (node id, depth)

  void euler_tour_(TreeNode *root, int depth)
  {
    if (root == nullptr)
      return;

    vertices_[root->val] = root;
    tt_.emplace_back(root->val, depth);

    euler_tour_(root->left, depth + 1);
    tt_.emplace_back(root->val, depth);
    euler_tour_(root->right, depth + 1);
  }

public:
  TreeNode *lcaDeepestLeaves(TreeNode *root)
  {
    euler_tour_(root, 1);
    int max_depth{};
    for (const auto &[node, depth] : tt_)
      max_depth = std::max(max_depth, depth);

    int n{static_cast<int>(tt_.size())};
    int start_idx{}, end_idx{n - 1};
    for (int i = 0; i < n; i++)
    {
      const auto &[node, depth] = tt_[i];
      if (depth == max_depth)
      {
        start_idx = i;
        break;
      }
    }

    for (int i = n - 1; i >= 0; i--)
    {
      const auto &[node, depth] = tt_[i];
      if (depth == max_depth)
      {
        end_idx = i;
        break;
      }
    }

    int min_depth{INT_MAX};
    TreeNode *lca{};
    for (int i = start_idx; i <= end_idx; i++)
    {
      const auto &[node, depth] = tt_[i];
      if (depth < min_depth)
      {
        min_depth = depth;
        lca       = vertices_[node];
      }
    }

    return lca;
  }
};
