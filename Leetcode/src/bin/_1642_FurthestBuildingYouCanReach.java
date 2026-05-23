import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

class Solution {
  public int furthestBuilding(int[] h, int bricks, int ladders) {
    int n = h.length;
    TreeMultiset<Integer> jumps = new TreeMultiset<>();

    for (int i = 0; i < n - 1; i++) {
      int diff = h[i + 1] - h[i];

      if (diff > 0) {
        if (ladders > 0) {
          jumps.add(diff);
          ladders -= 1;
        } else if (!jumps.isEmpty() && diff > jumps.first()) {
          int mn = jumps.first();
          bricks -= mn;
          if (bricks < 0) {
            return i;
          }
          jumps.removeOne(mn);
          jumps.add(diff);
        } else {
          bricks -= diff;
          if (bricks < 0) {
            return i;
          }
        }
      }
    }

    return n - 1;
  }
}

class TreeMultiset<E> {
  private TreeMap<E, Integer> map;
  private int size;

  public TreeMultiset() {
    this.map = new TreeMap<E, Integer>();
    this.size = 0;
  }

  public TreeMultiset(Comparator<? super E> comparator) {
    this.map = new TreeMap<E, Integer>(comparator);
    this.size = 0;
  }

  public boolean add(E e) {
    this.map.merge(e, 1, Integer::sum);
    this.size += 1;
    return true;
  }

  public E ceiling(E e) {
    return this.map.ceilingKey(e);
  }

  public void clear() {
    this.map.clear();
    this.size = 0;
  }

  @Override
  public TreeMultiset<E> clone() {
    TreeMultiset<E> cloned = new TreeMultiset<>(this.map.comparator());
    cloned.map.putAll(this.map);
    cloned.size = this.size;
    return cloned;
  }

  public Comparator<? super E> comparator() {
    return this.map.comparator();
  }

  public boolean contains(Object o) {
    return this.map.containsKey(o);
  }

  public E first() {
    return this.map.firstKey();
  }

  public E floor(E e) {
    return this.map.floorKey(e);
  }

  public E higher(E e) {
    return this.map.higherKey(e);
  }

  public boolean isEmpty() {
    return this.size == 0;
  }

  public E last() {
    return this.map.lastKey();
  }

  public E lower(E e) {
    return this.map.lowerKey(e);
  }

  public int size() {
    return this.size;
  }

  public int count(E e) {
    return this.map.getOrDefault(e, 0);
  }

  public Set<E> elementSet() {
    return this.map.keySet();
  }

  public Set<Map.Entry<E, Integer>> entryMultiset() {
    return this.map.entrySet();
  }

  public boolean removeOne(E e) {
    if (!this.map.containsKey(e))
      return false;

    Integer cnt = this.map.get(e);
    if (cnt == 1)
      this.map.remove(e);
    else
      this.map.put(e, --cnt);

    this.size -= 1;
    return true;
  }

  public boolean removeAll(E e) {
    if (!this.map.containsKey(e))
      return false;

    Integer cnt = this.map.get(e);
    this.map.remove(e);
    this.size -= cnt;
    return true;
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
