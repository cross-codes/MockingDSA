#include "TreeNode.hh"
#include <climits>
#include <vector>

class Solution
{
private:
  std::vector<std::pair<TreeNode *, int>> tree_traversal_;
  bool found_p_{}, found_q_{};
  __ssize_t p_index_{-1}, q_index_{-1}, depth_{0};

  void dfs_(TreeNode *root, TreeNode *p, TreeNode *q)
  {
    if (root == nullptr)
      return;

    ++depth_;
    tree_traversal_.emplace_back(root, depth_);

    if (root->val == q->val && !found_q_)
    {
      found_q_ = true;
      q_index_ = tree_traversal_.size() - 1;
    }

    if (root->val == p->val && !found_p_)
    {
      found_p_ = true;
      p_index_ = tree_traversal_.size() - 1;
    }

    dfs_(root->left, p, q);
    tree_traversal_.emplace_back(root, depth_);
    --depth_;
    dfs_(root->right, p, q);
  }

public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
  {
    dfs_(root, p, q);

    TreeNode *lca;
    int min_depth{INT_MAX};
    if (p_index_ > q_index_)
      std::swap(p_index_, q_index_);
    for (__ssize_t i = p_index_; i <= q_index_; i++)
    {
      auto &pair = tree_traversal_[i];
      if (min_depth > pair.second)
      {
        lca       = pair.first;
        min_depth = pair.second;
      }
    }

    return lca;
  }
};
