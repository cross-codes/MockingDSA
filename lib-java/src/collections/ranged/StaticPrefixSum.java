package collections.ranged;

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

  long rangeSum(int a, int b) {
    return prefix[b] - prefix[a];
  }
}
