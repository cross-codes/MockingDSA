#include "TreeNode.hh"
#include <deque>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> levelOrder(TreeNode *root)
  {
    if (root == nullptr)
      return {};

    std::deque<TreeNode *> queue{};
    queue.push_back(root);
    std::vector<std::vector<int>> res{};
    while (!queue.empty())
    {
      std::vector<int> level{};
      std::size_t nodes = queue.size();
      for (std::size_t i = 0; i < nodes; i++)
      {
        TreeNode *node = queue.back();

        if (node->left != nullptr)
          queue.push_front(node->left);
        if (node->right != nullptr)
          queue.push_front(node->right);

        level.push_back(node->val);
        queue.pop_back();
      }

      res.push_back(level);
    }

    return res;
  }
};
