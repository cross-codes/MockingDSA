package collections.ranged;

import java.util.Arrays;
import java.util.function.LongBinaryOperator;

import util.Algebra;

interface LongIntegerIntegerLongTriFunction {
  long apply(long t, int u, int v);
}

class LazySegmentTree {
  private final long[] tree;
  private final long[] lazy;
  private final long queryDefaultValue;
  private final long updateDefaultValue;
  private final LongBinaryOperator queryOperator;
  private final LongBinaryOperator mergeOperator;
  private final LongIntegerIntegerLongTriFunction batchFunction;

  public LazySegmentTree(long[] elements, long queryDefaultValue, long updateDefaultValue,
      LongBinaryOperator queryOperator, LongBinaryOperator mergeOperator,
      LongIntegerIntegerLongTriFunction batchFunction) {
    int offset = 1 << Algebra.ceilLog2(elements.length);
    tree = new long[offset << 1];
    System.arraycopy(elements, 0, tree, offset, elements.length);
    Arrays.fill(tree, offset + elements.length, tree.length, queryDefaultValue);
    for (int i = offset >> 1; i != 0; i >>= 1) {
      for (int k = i; k < i << 1; k++)
        tree[k] = queryOperator.applyAsLong(tree[k << 1], tree[k << 1 | 1]);
    }
    lazy = new long[tree.length];
    Arrays.fill(lazy, updateDefaultValue);
    this.queryDefaultValue = queryDefaultValue;
    this.updateDefaultValue = updateDefaultValue;
    this.queryOperator = queryOperator;
    this.mergeOperator = mergeOperator;
    this.batchFunction = batchFunction;
  }

  public long query(int from, int to) {
    int segmentIndex = 1;
    int segmentFrom = 0;
    int segmentTo = tree.length >> 1;
    if (from == segmentFrom && to == segmentTo)
      return querySegment(segmentIndex, segmentFrom, segmentTo);
    while (true) {
      if (to == segmentTo)
        return queryLeft(segmentIndex, segmentFrom, segmentTo, from);
      else if (from == segmentFrom)
        return queryRight(segmentIndex, segmentFrom, segmentTo, to);
      else {
        propagate(segmentIndex, segmentFrom, segmentTo);
        int segmentMiddle = segmentFrom + segmentTo >> 1;
        if (to <= segmentMiddle) {
          segmentIndex <<= 1;
          segmentTo = segmentMiddle;
        } else if (from >= segmentMiddle) {
          segmentIndex = segmentIndex << 1 | 1;
          segmentFrom = segmentMiddle;
        } else
          return queryOperator.applyAsLong(queryLeft(segmentIndex << 1, segmentFrom, segmentMiddle, from),
              queryRight(segmentIndex << 1 | 1, segmentMiddle, segmentTo, to));
      }
    }
  }

  private long queryLeft(int segmentIndex, int segmentFrom, int segmentTo, int from) {
    long result = queryDefaultValue;
    while (true) {
      propagate(segmentIndex, segmentFrom, segmentTo);
      int segmentMiddle = segmentFrom + segmentTo >> 1;
      if (from > segmentMiddle) {
        segmentIndex = segmentIndex << 1 | 1;
        segmentFrom = segmentMiddle;
      } else {
        result = queryOperator.applyAsLong(querySegment(segmentIndex << 1 | 1, segmentMiddle, segmentTo), result);
        if (from < segmentMiddle) {
          segmentIndex <<= 1;
          segmentTo = segmentMiddle;
        } else
          return result;
      }
    }
  }

  private long queryRight(int segmentIndex, int segmentFrom, int segmentTo, int to) {
    long result = queryDefaultValue;
    while (true) {
      propagate(segmentIndex, segmentFrom, segmentTo);
      int segmentMiddle = segmentFrom + segmentTo >> 1;
      if (to < segmentMiddle) {
        segmentIndex <<= 1;
        segmentTo = segmentMiddle;
      } else {
        result = queryOperator.applyAsLong(result, querySegment(segmentIndex << 1, segmentFrom, segmentMiddle));
        if (to > segmentMiddle) {
          segmentIndex = segmentIndex << 1 | 1;
          segmentFrom = segmentMiddle;
        } else
          return result;
      }
    }
  }

  private long querySegment(int segmentIndex, int segmentFrom, int segmentTo) {
    return lazy[segmentIndex] == updateDefaultValue ? tree[segmentIndex]
        : mergeOperator.applyAsLong(tree[segmentIndex],
            batchFunction.apply(lazy[segmentIndex], segmentFrom, segmentTo));
  }

  public void update(int from, int to, long value) {
    if (from == 0 && to == tree.length >> 1)
      lazy[1] = mergeOperator.applyAsLong(lazy[1], value);
    else
      update(1, 0, tree.length >> 1, from, to, value);
  }

  private void update(int segmentIndex, int segmentFrom, int segmentTo, int from, int to, long value) {
    if (to == segmentTo)
      updateLeft(segmentIndex, segmentFrom, segmentTo, from, value);
    else if (from == segmentFrom)
      updateRight(segmentIndex, segmentFrom, segmentTo, to, value);
    else {
      propagate(segmentIndex, segmentFrom, segmentTo);
      int segmentMiddle = segmentFrom + segmentTo >> 1;
      if (to <= segmentMiddle)
        update(segmentIndex << 1, segmentFrom, segmentMiddle, from, to, value);
      else if (from >= segmentMiddle)
        update(segmentIndex << 1 | 1, segmentMiddle, segmentTo, from, to, value);
      else {
        updateLeft(segmentIndex << 1, segmentFrom, segmentMiddle, from, value);
        updateRight(segmentIndex << 1 | 1, segmentMiddle, segmentTo, to, value);
      }
      tree[segmentIndex] = queryOperator.applyAsLong(querySegment(segmentIndex << 1, segmentFrom, segmentMiddle),
          querySegment(segmentIndex << 1 | 1, segmentMiddle, segmentTo));
    }
  }

  private void updateLeft(int segmentIndex, int segmentFrom, int segmentTo, int from, long value) {
    propagate(segmentIndex, segmentFrom, segmentTo);
    int segmentMiddle = segmentFrom + segmentTo >> 1;
    if (from > segmentMiddle)
      updateLeft(segmentIndex << 1 | 1, segmentMiddle, segmentTo, from, value);
    else {
      lazy[segmentIndex << 1 | 1] = mergeOperator.applyAsLong(lazy[segmentIndex << 1 | 1], value);
      if (from < segmentMiddle)
        updateLeft(segmentIndex << 1, segmentFrom, segmentMiddle, from, value);
    }
    tree[segmentIndex] = queryOperator.applyAsLong(querySegment(segmentIndex << 1, segmentFrom, segmentMiddle),
        querySegment(segmentIndex << 1 | 1, segmentMiddle, segmentTo));
  }

  private void updateRight(int segmentIndex, int segmentFrom, int segmentTo, int to, long value) {
    propagate(segmentIndex, segmentFrom, segmentTo);
    int segmentMiddle = segmentFrom + segmentTo >> 1;
    if (to < segmentMiddle)
      updateRight(segmentIndex << 1, segmentFrom, segmentMiddle, to, value);
    else {
      lazy[segmentIndex << 1] = mergeOperator.applyAsLong(lazy[segmentIndex << 1], value);
      if (to > segmentMiddle)
        updateRight(segmentIndex << 1 | 1, segmentMiddle, segmentTo, to, value);
    }
    tree[segmentIndex] = queryOperator.applyAsLong(querySegment(segmentIndex << 1, segmentFrom, segmentMiddle),
        querySegment(segmentIndex << 1 | 1, segmentMiddle, segmentTo));
  }

  private void propagate(int segmentIndex, int segmentFrom, int segmentTo) {
    if (lazy[segmentIndex] != updateDefaultValue) {
      tree[segmentIndex] = mergeOperator.applyAsLong(tree[segmentIndex],
          batchFunction.apply(lazy[segmentIndex], segmentFrom, segmentTo));
      lazy[segmentIndex << 1] = mergeOperator.applyAsLong(lazy[segmentIndex << 1], lazy[segmentIndex]);
      lazy[segmentIndex << 1 | 1] = mergeOperator.applyAsLong(lazy[segmentIndex << 1 | 1], lazy[segmentIndex]);
      lazy[segmentIndex] = updateDefaultValue;
    }
  }
}
