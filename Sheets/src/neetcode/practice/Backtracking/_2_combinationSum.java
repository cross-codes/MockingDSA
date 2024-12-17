package neetcode.practice.Backtracking;

import java.util.ArrayList;
import java.util.List;

class Solution {
  final public List<List<Integer>> result = new ArrayList<>();
  final public List<Integer> augment = new ArrayList<>();

  public List<List<Integer>> combinationSum(int[] nums, int target) {
    this.dfs(0, 0, target, nums);
    return this.result;
  }

  private void dfs(int index, int currentSum, int target, int[] nums) {
    if (currentSum == target) {
      this.result.add(new ArrayList<>(this.augment));
      return;
    }

    if ((index >= nums.length) || currentSum > target)
      return;

    this.augment.add(nums[index]);
    this.dfs(index, currentSum + nums[index], target, nums);

    this.augment.remove(this.augment.size() - 1);
    this.dfs(index + 1, currentSum, target, nums);
  }
}