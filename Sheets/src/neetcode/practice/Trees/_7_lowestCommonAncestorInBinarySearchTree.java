package neetcode.practice.Trees;

import java.util.ArrayList;
import java.util.Collections;

class Solution {
  boolean[] checkTarget = new boolean[2];

  public void dfs(TreeNode root, TreeNode target, ArrayList<TreeNode> ancestors, int variant) {
    if (root == null)
      return;
    if (root.val == target.val) {
      this.checkTarget[variant] = true;
      ancestors.add(root);
      return;
    }

    if (!this.checkTarget[variant])
      this.dfs(root.left, target, ancestors, variant);
    if (!this.checkTarget[variant])
      this.dfs(root.right, target, ancestors, variant);
    if (this.checkTarget[variant]) {
      ancestors.add(root);
    }
  }

  public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
    ArrayList<TreeNode> ancestorsOfP = new ArrayList<>(), ancestorsOfQ = new ArrayList<>();
    this.dfs(root, p, ancestorsOfP, 0);
    this.dfs(root, q, ancestorsOfQ, 1);

    Collections.reverse(ancestorsOfP);
    Collections.reverse(ancestorsOfQ);
    int maxIterationSize = Math.min(ancestorsOfP.size(), ancestorsOfQ.size());

    for (int i = 0; i < maxIterationSize; i++) {
      if (ancestorsOfP.get(i).val != ancestorsOfQ.get(i).val)
        return ancestorsOfP.get(i - 1);
    }

    if (ancestorsOfP.size() == maxIterationSize)
      return ancestorsOfP.get(maxIterationSize - 1);
    else
      return ancestorsOfQ.get(maxIterationSize - 1);
  }
}