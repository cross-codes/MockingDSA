package neetcode.practice.Trees;

class Solution {
  public boolean isBalanced = true;

  public int dfs(TreeNode root) {
    if (root == null)
      return 0;

    int leftHeight = dfs(root.left);
    int rightHeight = dfs(root.right);

    if (Math.abs(leftHeight - rightHeight) > 1)
      this.isBalanced = false;

    return 1 + Math.max(leftHeight, rightHeight);
  }

  public boolean isBalanced(TreeNode root) {
    this.dfs(root);
    return this.isBalanced;
  }
}