import java.util.Arrays;

class Solution {
  public int minimumSwaps(int[] nums) {
    int[] cpy = nums.clone();
    Arrays.sort(cpy);
    int cnt = 0, n = nums.length;
    for (int i = 0; i < n; i++) {
      cnt += (nums[i] == 0 && cpy[n - i - 1] != 0) ? 1 : 0;
    }

    return cnt;
  }
}
