import java.util.Arrays;
import java.util.Iterator;
import java.util.function.IntFunction;

class Solution {
  public int totalWaviness(int num1, int num2) {
    IntFunction<Integer> waviness = (n) -> {
      IntVector digits = new IntVector();
      while (n != 0) {
        digits.add(n % 10);
        n /= 10;
      }

      int sz = digits.size(), wv = 0;
      for (int i = 1; i < sz - 1; i++) {
        int curr = digits.get(i), prev = digits.get(i - 1), next = digits.get(i + 1);
        if (curr > prev && curr > next)
          wv += 1;
        else if (curr < prev && curr < next)
          wv += 1;
      }

      return wv;
    };

    int gwv = 0;
    for (int e = num1; e <= num2; e++) {
      gwv += waviness.apply(e);
    }

    return gwv;
  }
}

class IntVector implements Cloneable, Iterable<Integer> {
  private static final int[] EMPTY = new int[0];
  private int[] array;
  private int size;

  public IntVector() {
    array = EMPTY;
  }

  public IntVector(int n) {
    array = new int[n];
  }

  public int size() {
    return size;
  }

  public IntVector clone() {
    try {
      IntVector clone = (IntVector) super.clone();
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
        ensureCapacity(size << 1);
    }
    array[size++] = e;
  }

  public void ensureCapacity(int capacity) {
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
