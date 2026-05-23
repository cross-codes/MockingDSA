class Solution {
  public boolean check(int[] nums) {
    int n = nums.length;
    boolean breakp = false;
    int mn = Integer.MAX_VALUE;
    for (int i = 0; i < n - 1; i++) {
      if (breakp) {
        if (nums[i] > nums[i + 1] || nums[i] > mn)
          return false;
      }

      if (!breakp) {
        if (nums[i] > nums[i + 1]) {
          breakp = true;
        }
        mn = Math.min(mn, nums[i]);
      }
    }

    return !breakp || nums[n - 1] <= mn;
  }
}
