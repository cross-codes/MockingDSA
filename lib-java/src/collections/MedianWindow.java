package collections;

public class MedianWindow {
  private int[] array;
  private int currentBegin, currentEnd, windowSize;
  private int expectedLowSize, expectedHighSize;

  public TreeMultiset<Long> low, high;
  public long lowerSum, higherSum;

  void balanceSets() {
    while (low.size() < expectedLowSize) {
      long val = high.first();
      low.add(val);
      lowerSum += val;
      higherSum -= val;
      high.removeOne(val);
    }

    while (high.size() < expectedHighSize) {
      long val = low.last();
      higherSum += val;
      high.add(val);
      lowerSum -= val;
      low.removeOne(val);
    }
  }

  public MedianWindow(int[] array, int k) {
    this.currentBegin = 0;
    this.currentEnd = 0;
    this.windowSize = k;
    this.array = new int[array.length];
    System.arraycopy(array, 0, this.array, 0, array.length);

    if ((k & 1) != 0) {
      expectedLowSize = (k >> 1) + 1;
      expectedHighSize = k >> 1;
    } else {
      expectedLowSize = expectedHighSize = k >> 1;
    }

    for (int i = 0; i < windowSize; i++) {
      low.add((long) array[i]);
      lowerSum += array[i];
    }

    balanceSets();
  }

  long nextMedian() {
    if (currentEnd == 0) {
      currentEnd = windowSize;
      return low.first();
    }

    long r = array[currentBegin++];

    if (low.contains(r)) {
      lowerSum -= r;
      low.removeOne(r);
    } else {
      higherSum -= r;
      high.removeOne(r);
    }

    long e = array[currentEnd++];
    if (!high.isEmpty() && e > high.first()) {
      higherSum += e;
      high.add(e);
    } else {
      lowerSum += e;
      low.add(e);
    }

    balanceSets();
    return low.last();
  }
}
