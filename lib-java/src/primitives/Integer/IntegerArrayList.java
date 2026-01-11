package primitives.Integer;

import java.util.Arrays;
import java.util.Iterator;

public class IntegerArrayList implements Cloneable, Iterable<Integer> {
  private static final int[] EMPTY = new int[0];
  private int[] array;
  private int size;

  public IntegerArrayList() {
    array = EMPTY;
  }

  public IntegerArrayList(int n) {
    array = new int[n];
  }

  public int size() {
    return size;
  }

  public IntegerArrayList clone() {
    try {
      IntegerArrayList clone = (IntegerArrayList) super.clone();
      clone.array = size == 0 ? EMPTY : array.clone();
      return clone;
    } catch (CloneNotSupportedException ex) {
      throw new RuntimeException();
    }
  }

  public Iterator<Integer> iterator() {
    return new IALIterator();
  }

  public void add(int e) {
    if (array.length == size) {
      if (array.length == 0)
        array = new int[4];
      else
        grow(size << 1);
    }
    array[size++] = e;
  }

  private void grow(int capacity) {
    int[] array = new int[capacity];
    System.arraycopy(this.array, 0, array, 0, size);
    this.array = array;
  }

  public int get(int index) {
    return array[index];
  }

  public void set(int index, int e) {
    array[index] = e;
  }

  public int remove() {
    return array[--size];
  }

  public void clear() {
    size = 0;
  }

  public int[] toArray() {
    int[] array = new int[size];
    System.arraycopy(this.array, 0, array, 0, size);
    return array;
  }

  public void sort() {
    Arrays.sort(array, 0, size);
  }

  private class IALIterator implements Iterator<Integer> {
    private int index;

    public boolean hasNext() {
      return index != size;
    }

    public Integer next() {
      return array[index++];
    }
  }
}
