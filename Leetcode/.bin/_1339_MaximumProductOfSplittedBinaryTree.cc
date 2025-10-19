#include "TreeNode.hh"

#include <cstdint>
#include <unordered_map>

class Solution
{
public:
  int maxProduct(TreeNode *root)
  {
    constexpr int64_t MOD = static_cast<int64_t>(1e9 + 7);
    std::unordered_map<TreeNode *, int64_t> subtree_sums{};

    auto dfs = [&subtree_sums](auto &&dfs, TreeNode *root) -> int64_t {
      if (root == nullptr)
        return 0;

      subtree_sums[root] =
          dfs(dfs, root->left) + dfs(dfs, root->right) + root->val;
      return subtree_sums[root];
    };

    int64_t tot_sum = dfs(dfs, root);
    int64_t mx_prod = {INT64_MIN};

    auto dfs2       = [&subtree_sums, &tot_sum, &mx_prod](auto &&dfs2,
                                                    TreeNode *root) -> void {
      if (root == nullptr)
        return;

      int64_t left  = subtree_sums[root->left];
      int64_t right = subtree_sums[root->right];
      mx_prod       = std::max(mx_prod, left * (tot_sum - left));
      mx_prod       = std::max(mx_prod, right * (tot_sum - right));
      dfs2(dfs2, root->left);
      dfs2(dfs2, root->right);
    };

    dfs2(dfs2, root);

    return mx_prod % MOD;
  }
};
