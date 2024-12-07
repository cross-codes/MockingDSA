package neetcode.practice.Trees;

class Solution {

  public int dfs(TreeNode root) {
    if (root == null)
      return 0;

    int leftHeight = dfs(root.left);
    int rightHeight = dfs(root.right);

    return 1 + Math.max(leftHeight, rightHeight);
  }

  public int maxDepth(TreeNode root) {
    return this.dfs(root);
  }
}