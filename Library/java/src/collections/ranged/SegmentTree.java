package collections.ranged;

import java.util.Arrays;
import java.util.function.LongBinaryOperator;

class SegmentTree {
  private int n, offset;
  private long[] tree;
  private LongBinaryOperator function;
  private long defaultValue;

  SegmentTree(LongBinaryOperator function, long[] array, long defaultValue) {
    this.n = array.length;
    this.function = function;
    this.defaultValue = defaultValue;

    this.offset = 1 << (32 - Integer.numberOfLeadingZeros(n - 1));
    this.tree = new long[offset << 1];
    Arrays.fill(tree, defaultValue);

    System.arraycopy(array, 0, tree, offset, array.length);

    int i = offset;
    while (i != 1) {
      int j = i;
      while (j < i << 1) {
        tree[j >> 1] = function.applyAsLong(tree[j], tree[j + 1]);
        j += 2;
      }

      i >>= 1;
    }
  }

  public void setAtIndex(int index, long value) {
    index += offset;
    tree[index] = value;

    while (index != 1) {
      tree[index >> 1] = function.applyAsLong(tree[index], tree[index ^ 1]);
      index >>= 1;
    }
  }

  public long rangeQuery(int a, int b) {
    a += offset;
    b += offset;

    long result = defaultValue;
    while (a < b) {
      if ((a & 1) != 0) {
        result = function.applyAsLong(result, tree[a++]);
      }

      if ((b & 1) != 0) {
        result = function.applyAsLong(result, tree[--b]);
      }

      a >>= 1;
      b >>= 1;
    }

    return result;
  }
}
