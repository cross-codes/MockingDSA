import java.util.function.LongBinaryOperator;

class Solution {
  public int countLocalMaximums(int[][] matrix) {
    int n = matrix.length, m = matrix[0].length;

    long[][] M = new long[n][m];
    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++) {
        M[y][x] = matrix[y][x];
      }

    IdempotentSparseTable[] rowTables = new IdempotentSparseTable[n];

    for (int y = 0; y < n; y++)
      rowTables[y] = new IdempotentSparseTable((a, b) -> Math.max(a, b), M[y]);

    IntToIntBiFunction localMaxima = (Y, X) -> {
      int e = matrix[Y][X];
      long mx = Long.MIN_VALUE;
      for (int y = Math.max(0, Y - e + 1); y < Math.min(n, Y + e); y++)
        mx = Math.max(mx, rowTables[y].rangeQuery(Math.max(0, X - e), Math.min(m, X + e + 1)));
      if (Y - e >= 0)
        mx = Math.max(mx, rowTables[Y - e].rangeQuery(Math.max(0, X - e + 1), Math.min(m, X + e)));
      if (Y + e < n)
        mx = Math.max(mx, rowTables[Y + e].rangeQuery(Math.max(0, X - e + 1), Math.min(m, X + e)));

      return (int) mx;
    };

    int cnt = 0;
    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
        if (M[y][x] > 0 && localMaxima.getAsInt(y, x) <= M[y][x])
          cnt += 1;

    return cnt;
  }
}

@FunctionalInterface
interface IntToIntBiFunction {
  int getAsInt(int Y, int X);
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
