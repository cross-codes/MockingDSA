package collections.ranged;

class DifferenceArray {
  private long[] diff;
  private SegmentTree tree;

  DifferenceArray(long[] array) {
    diff = new long[array.length + 1];
    diff[0] = array[0];
    for (int i = 1; i < array.length; i++) {
      diff[i] = array[i] - array[i - 1];
    }

    tree = new SegmentTree(Long::sum, diff, 0);
  }

  public void increaseInRange(int a, int b, long x) {
    tree.setAtIndex(a, diff[a] + x);
    diff[a] += x;

    tree.setAtIndex(b, diff[b] - x);
    diff[b] -= x;
  }

  public long getUnderlyingValue(int index) {
    return tree.rangeQuery(0, index + 1);
  }
}
