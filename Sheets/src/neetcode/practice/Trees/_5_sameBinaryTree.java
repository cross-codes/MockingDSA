package neetcode.practice.Trees;

import java.util.ArrayList;

class Solution {
  public ArrayList<Integer> pDescriptor = new ArrayList<>();
  public ArrayList<Integer> qDescriptor = new ArrayList<>();

  public void dfs(TreeNode root, ArrayList<Integer> descriptor) {
    if (root == null) {
      descriptor.add(null);
      return;
    }

    descriptor.add(root.val);

    this.dfs(root.left, descriptor);
    this.dfs(root.right, descriptor);
  }

  public boolean isSameTree(TreeNode p, TreeNode q) {
    this.dfs(p, this.pDescriptor);
    this.dfs(q, this.qDescriptor);
    return pDescriptor.equals(qDescriptor);
  }
}