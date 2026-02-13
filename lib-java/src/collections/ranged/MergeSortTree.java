package collections.ranged;

import primitives.Integer.IntegerArrayList;

public class MergeSortTree {
  private int l, r;
  private IntegerArrayList list;
  private MergeSortTree left, right;

  public MergeSortTree(int from, int excludeTo, int[] elements) {
    this.l = from;
    this.r = excludeTo;
    this.list = new IntegerArrayList();

    if (excludeTo - from == 1) {
      this.list.add(elements[from]);
      left = right = null;
    } else {
      int mid = from + (excludeTo - from) / 2;
      left = new MergeSortTree(from, mid, elements);
      right = new MergeSortTree(mid, excludeTo, elements);

      list.ensureCapacity(excludeTo - from);
      merge(left.list, right.list);
    }
  }

  private void merge(IntegerArrayList left, IntegerArrayList right) {
    int i = 0, j = 0;

    this.list.clear();

    while (i < left.size() && j < right.size()) {
      if (left.get(i) <= right.get(j)) {
        this.list.add(left.get(i));
        i++;
      } else {
        this.list.add(right.get(j));
        j++;
      }
    }

    while (i < left.size()) {
      this.list.add(left.get(i));
      i++;
    }

    while (j < right.size()) {
      this.list.add(right.get(j));
      j++;
    }
  }

  public int count(int from, int excludeTo, int inclusiveRangeStart, int inclusiveRangeEnd) {
    if (from >= this.r || excludeTo <= this.l) {
      return 0;
    }

    if (this.l >= from && this.r <= excludeTo) {
      int L = -1, R = list.size();
      while (R - L > 1) {
        int M = L + ((R - L) >> 1);
        if (list.get(M) >= inclusiveRangeStart) {
          R = M;
        } else {
          L = M;
        }
      }

      int idx1 = R;

      L = -1;
      R = list.size();
      while (R - L > 1) {
        int M = L + ((R - L) >> 1);
        if (list.get(M) > inclusiveRangeEnd) {
          R = M;
        } else {
          L = M;
        }
      }

      int idx2 = R;

      return idx2 - idx1;
    }

    return this.left.count(from, excludeTo, inclusiveRangeStart, inclusiveRangeEnd)
        + this.right.count(from, excludeTo, inclusiveRangeStart, inclusiveRangeEnd);
  }
}
