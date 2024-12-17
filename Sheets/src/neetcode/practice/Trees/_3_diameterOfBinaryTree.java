package neetcode.practice.Trees;

class Solution {
  int res = 0;

  public int dfs(TreeNode root, Procedure proc) {
    if (root == null)
      return 0;

    int leftHeight = dfs(root.left, proc);
    int rightHeight = dfs(root.right, proc);

    proc.run(leftHeight + rightHeight);

    return 1 + Math.max(leftHeight, rightHeight);
  }

  public int diameterOfBinaryTree(TreeNode root) {
    Procedure proc = update -> this.res = Math.max(this.res, update);
    this.dfs(root, proc);
    return this.res;
  }
}

interface Procedure {
  public void run(int update);
}