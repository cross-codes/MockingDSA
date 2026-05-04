package collections.ranged;

import java.util.function.LongBinaryOperator;

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
