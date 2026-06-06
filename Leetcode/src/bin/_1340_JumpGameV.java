import java.util.Arrays;
import java.util.function.LongBinaryOperator;

class Solution {
  public int maxJumps(int[] a, int d) {
    int n = a.length;
    long[] arr = new long[n];
    for (int i = 0; i < n; i++) {
      arr[i] = a[i];
    }

    IdempotentSparseTable table = new IdempotentSparseTable(Math::max, arr);

    int[] best = new int[n];
    DFS dfs = (instance, i) -> {
      if (best[i] != -1) {
        return best[i];
      }

      int res = 0;
      for (int j = i + 1; j <= Math.min(n - 1, i + d); j++) {
        if (table.rangeQuery(i + 1, j + 1) < arr[i]) {
          res = Math.max(res, 1 + instance.run(instance, j));
        } else {
          break;
        }
      }

      for (int j = i - 1; j >= Math.max(0, i - d); j--) {
        if (table.rangeQuery(j, i) < arr[i]) {
          res = Math.max(res, 1 + instance.run(instance, j));
        } else {
          break;
        }
      }

      return best[i] = res;
    };

    Arrays.fill(best, -1);
    int gmx = 0;
    for (int i = 0; i < n; i++) {
      if (best[i] == -1) {
        gmx = Math.max(gmx, dfs.run(dfs, i));
      }
    }

    return 1 + gmx;
  }
}

@FunctionalInterface
interface DFS {
  int run(DFS instance, int idx);
}

class IdempotentSparseTable {
  private LongBinaryOperator function;
  private long[][] table;
  private int n;

  IdempotentSparseTable(LongBinaryOperator func, long[] array) {
    this.function = func;
    this.n = array.length;

    int K = 31 - Integer.numberOfLeadingZeros(n);
    table = new long[K + 1][n];
    System.arraycopy(array, 0, table[0], 0, array.length);

    for (int y = 1; y < table.length; y++) {
      for (int x = 0, k = 1 << (y - 1); x <= n - (1 << y); x++, k++) {
        table[y][x] = function.applyAsLong(table[y - 1][x], table[y - 1][k]);
      }
    }
  }

  public long rangeQuery(int a, int b) {
    int row = 31 - Integer.numberOfLeadingZeros(b - a);
    return function.applyAsLong(table[row][a], table[row][b - (1 << row)]);
  }
}
