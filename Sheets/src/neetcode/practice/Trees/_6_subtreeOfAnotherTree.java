package neetcode.practice.Trees;

import java.util.ArrayList;

class Solution {
  public ArrayList<Integer> pDescriptor = new ArrayList<>();
  public ArrayList<Integer> qDescriptor = new ArrayList<>();
  public boolean isSubTree = false;

  public void dfs(TreeNode root, ArrayList<Integer> descriptor) {
    if (root == null) {
      descriptor.add(null);
      return;
    }

    descriptor.add(root.val);

    this.dfs(root.left, descriptor);
    this.dfs(root.right, descriptor);
  }

  public void isSameTree(TreeNode p, TreeNode q) {
    this.dfs(p, this.pDescriptor);
    if (pDescriptor.equals(qDescriptor))
      this.isSubTree = true;

    pDescriptor = new ArrayList<>();
  }

  public void dfs(TreeNode root, TreeNode checkRoot) {
    if (root == null)
      return;

    this.isSameTree(root, checkRoot);

    this.dfs(root.left, checkRoot);
    this.dfs(root.right, checkRoot);
  }

  public boolean isSubtree(TreeNode root, TreeNode subRoot) {
    this.dfs(subRoot, this.qDescriptor);
    dfs(root, subRoot);
    return this.isSubTree;
  }
}