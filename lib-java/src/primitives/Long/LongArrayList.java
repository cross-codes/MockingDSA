package primitives.Long;

import java.util.Arrays;
import java.util.Iterator;

public class LongArrayList implements Cloneable, Iterable<Long> {
  private static final long[] EMPTY = new long[0];
  private long[] array;
  private int size;

  public LongArrayList() {
    array = EMPTY;
  }

  public LongArrayList(int n) {
    array = new long[n];
  }

  public int size() {
    return size;
  }

  public LongArrayList clone() {
    try {
      LongArrayList clone = (LongArrayList) super.clone();
      clone.array = size == 0 ? EMPTY : array.clone();
      return clone;
    } catch (CloneNotSupportedException ex) {
      throw new RuntimeException();
    }
  }

  public Iterator<Long> iterator() {
    return new LALIterator();
  }

  public void add(int e) {
    if (array.length == size) {
      if (array.length == 0)
        array = new long[4];
      else
        grow(size << 1);
    }
    array[size++] = e;
  }

  private void grow(int capacity) {
    long[] array = new long[capacity];
    System.arraycopy(this.array, 0, array, 0, size);
    this.array = array;
  }

  public long get(int index) {
    return array[index];
  }

  public void set(int index, long e) {
    array[index] = e;
  }

  public long remove() {
    return array[--size];
  }

  public void clear() {
    size = 0;
  }

  public long[] toArray() {
    long[] array = new long[size];
    System.arraycopy(this.array, 0, array, 0, size);
    return array;
  }

  public void sort() {
    Arrays.sort(array, 0, size);
  }

  private class LALIterator implements Iterator<Long> {
    private int index;

    public boolean hasNext() {
      return index != size;
    }

    public Long next() {
      return array[index++];
    }
  }
}
