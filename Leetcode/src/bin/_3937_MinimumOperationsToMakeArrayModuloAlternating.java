class Solution {
  public int minOperations(int[] nums, int k) {
    int n = nums.length, gmn = Integer.MAX_VALUE;
    for (int x = 0; x < k; x++) {
      for (int y = 0; y < k; y++) {
        if (x == y)
          continue;
        int tot = 0;
        for (int i = 0; i < n; i++)
          tot += Math.min(k - Math.abs((nums[i] % k) - (((i & 1) == 0) ? x : y)),
              Math.abs((nums[i] % k) - (((i & 1) == 0) ? x : y)));
        gmn = Math.min(gmn, tot);
      }
    }

    return gmn;
  }
}
