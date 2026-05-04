class Solution {
  public int maxRotateFunction(int[] nums) {
    int n = nums.length;
    var prefix = new StaticPrefixSum(nums);

    long curr = 0;
    for (int i = 0; i < n; i++) {
      curr += i * nums[i];
    }

    long mx = curr;
    for (int i = 1; i < n; i++) {
      curr = curr + prefix.rangeSum(0, n - i) - ((n - 1) * nums[n - i]) + prefix.rangeSum(n - i + 1, n);
      mx = Math.max(curr, mx);
    }

    return (int) mx;
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
