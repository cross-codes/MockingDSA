package neetcode.practice.Trees;

class Solution {
  int res = 0;

  public int dfs(TreeNode root) {
    if (root == null)
      return 0;

    int leftHeight = dfs(root.left);
    int rightHeight = dfs(root.right);
    this.res = Math.max(res, leftHeight + rightHeight);
    return 1 + Math.max(leftHeight, rightHeight);
  }

  public int diameterOfBinaryTree(TreeNode root) {
    this.dfs(root);
    return this.res;
  }
}