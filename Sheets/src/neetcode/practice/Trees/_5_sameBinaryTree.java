package neetcode.practice.Trees;

import java.util.ArrayList;

class Solution {
  public ArrayList<Integer> pDescriptor = new ArrayList<>();
  public ArrayList<Integer> qDescriptor = new ArrayList<>();

  public void dfs(TreeNode root, ArrayList<Integer> descriptor, Procedure proc) {
    proc.run(root, descriptor);

    if (root == null)
      return;

    this.dfs(root.left, descriptor, proc);
    this.dfs(root.right, descriptor, proc);
  }

  public boolean isSameTree(TreeNode p, TreeNode q) {
    Procedure proc = (root, descriptor) -> descriptor.add(root == null ? null : root.val);
    this.dfs(p, this.pDescriptor, proc);
    this.dfs(q, this.qDescriptor, proc);
    return pDescriptor.equals(qDescriptor);
  }
}

interface Procedure {
  public void run(TreeNode root, ArrayList<Integer> descriptor);
}