class Solution {
  public int[] leftRightDifference(int[] nums) {
    int n = nums.length;
    int[] numsRev = new int[n];
    for (int i = 0; i < n; i++)
      numsRev[i] = nums[n - i - 1];

    var prefix = new StaticPrefixSum(nums);
    var suffix = new StaticPrefixSum(numsRev);

    int[] res = new int[n];
    for (int i = 0; i < n; i++) {
      res[i] = (int) Math.abs(prefix.rangeSum(0, i) - suffix.rangeSum(0, n - i - 1));
    }

    return res;
  }
}

class StaticPrefixSum {
  private long[] prefix;

  StaticPrefixSum(int[] array) {
    prefix = new long[array.length + 1];
    for (int i = 1; i <= array.length; i++) {
      prefix[i] = prefix[i - 1] + array[i - 1];
    }
  }

  StaticPrefixSum(long[] array) {
    prefix = new long[array.length + 1];
    for (int i = 1; i <= array.length; i++) {
      prefix[i] = prefix[i - 1] + array[i - 1];
    }
  }

  public long rangeSum(int a, int b) {
    return prefix[b] - prefix[a];
  }
}
