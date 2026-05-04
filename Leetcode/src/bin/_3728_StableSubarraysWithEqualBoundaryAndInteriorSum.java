import java.util.HashMap;

// rangeSum[l, r + 1) = prefix[r + 1] - prefix[l] = a[r] * 3
// prefix[l] = prefix[r + 1] - a[r] * 3
class Solution {
  private record LongOrderedPair(long first, long second) {
  }

  public long countStableSubarrays(int[] a) {
    int n = a.length;
    long[] prefix = new long[n + 1];
    for (int i = 1; i <= n; i++) {
      prefix[i] = prefix[i - 1] + a[i - 1];
    }

    long cnt = 0;
    HashMap<LongOrderedPair, Integer> freq = new HashMap<>();
    for (int r = 0; r < n; r++) {
      if (r >= 2) {
        freq.merge(new LongOrderedPair(prefix[r - 2], a[r - 2]), 1, Integer::sum);
      }
      cnt += freq.getOrDefault(new LongOrderedPair(prefix[r + 1] - 3L * a[r], a[r]), 0);
    }

    return cnt;
  }
}
