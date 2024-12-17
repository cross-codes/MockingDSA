package neetcode.practice.Backtracking;

import java.util.ArrayList;
import java.util.List;

class Solution {
  final public List<List<Integer>> result = new ArrayList<>();
  final public List<Integer> subset = new ArrayList<>();

  public List<List<Integer>> subsets(int[] nums) {
    this.dfs(nums, 0);
    return this.result;
  }

  private void dfs(int[] nums, int index) {
    if (index == nums.length) {
      this.result.add(new ArrayList<>(this.subset));
      return;
    }

    this.subset.add(nums[index]);
    this.dfs(nums, index + 1);
    this.subset.remove(this.subset.size() - 1);
    this.dfs(nums, index + 1);

  }
}