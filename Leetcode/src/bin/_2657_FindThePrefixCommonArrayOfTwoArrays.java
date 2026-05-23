import java.util.function.IntSupplier;

class Solution {
  public int[] findThePrefixCommonArray(int[] A, int[] B) {
    int n = A.length;
    boolean[] seenA = new boolean[n + 1], seenB = new boolean[n + 1];

    IntSupplier numCommon = () -> {
      int cnt = 0;
      for (int i = 1; i <= n; i++)
        cnt += seenA[i] && seenB[i] ? 1 : 0;

      return cnt;
    };

    int[] C = new int[n];
    for (int i = 0; i < n; i++) {
      seenA[A[i]] = true;
      seenB[B[i]] = true;
      C[i] = numCommon.getAsInt();
    }

    return C;
  }
}
