class Solution {
  public int compareBitonicSums(int[] nums) {
    int n = nums.length;

    int mx = nums[0], bidx = 0;
    for (int i = 1; i < n; i++) {
      if (nums[i] > mx) {
        mx = nums[i];
        bidx = i;
      }
    }

    var prefix = new StaticPrefixSum(nums);
    long asc = prefix.rangeSum(0, bidx);
    long desc = prefix.rangeSum(bidx + 1, n);

    if (asc > desc) {
      return 0;
    } else if (asc < desc) {
      return 1;
    } else {
      return -1;
    }
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
