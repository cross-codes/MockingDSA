package neetcode.practice.Trees;

class Solution {
  public TreeNode invertTree(TreeNode root) {
    Procedure proc = node -> {
      TreeNode temp = node.left;
      node.left = node.right;
      node.right = temp;
    };
    this.dfs(root, proc);
    return root;
  }

  private void dfs(TreeNode root, Procedure proc) {
    if (root == null)
      return;

    proc.run(root);

    this.dfs(root.left, proc);
    this.dfs(root.right, proc);
  }
}

interface Procedure {
  public void run(TreeNode root);
}