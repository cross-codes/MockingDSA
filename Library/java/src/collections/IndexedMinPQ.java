package collections;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class IndexedMinPQ<Key extends Comparable<Key>> implements Iterable<Integer> {
  private int maxN;
  private int n;
  private int[] pq;
  private int[] qp;
  private Key[] keys;

  @SuppressWarnings("unchecked")
  public IndexedMinPQ(int maxN) {
    if (maxN < 0)
      throw new IllegalArgumentException();
    this.maxN = maxN;
    n = 0;
    keys = (Key[]) new Comparable[maxN + 1];
    pq = new int[maxN + 1];
    qp = new int[maxN + 1];
    for (int i = 0; i <= maxN; i++)
      qp[i] = -1;
  }

  public boolean isEmpty() {
    return n == 0;
  }

  public boolean contains(int i) {
    validateIndex(i);
    return qp[i] != -1;
  }

  public int size() {
    return n;
  }

  public void insert(int i, Key key) {
    validateIndex(i);
    if (contains(i))
      throw new IllegalArgumentException("index is already in the priority queue");
    n++;
    qp[i] = n;
    pq[n] = i;
    keys[i] = key;
    swim(n);
  }

  public int minIndex() {
    if (n == 0)
      throw new NoSuchElementException("Priority queue underflow");
    return pq[1];
  }

  public Key minKey() {
    if (n == 0)
      throw new NoSuchElementException("Priority queue underflow");
    return keys[pq[1]];
  }

  public int removeMin() {
    if (n == 0)
      throw new NoSuchElementException("Priority queue underflow");
    int min = pq[1];
    xchg(1, n--);
    sink(1);
    assert min == pq[n + 1];
    qp[min] = -1;
    keys[min] = null;
    pq[n + 1] = -1;
    return min;
  }

  public Key get(int i) {
    validateIndex(i);
    if (!contains(i))
      throw new NoSuchElementException("index is not in the priority queue");
    else
      return keys[i];
  }

  public void set(int i, Key key) {
    validateIndex(i);
    if (!contains(i))
      throw new NoSuchElementException("index is not in the priority queue");
    keys[i] = key;
    swim(qp[i]);
    sink(qp[i]);
  }

  public void decreaseKey(int i, Key key) {
    validateIndex(i);
    if (!contains(i))
      throw new NoSuchElementException("index is not in the priority queue");
    if (keys[i].compareTo(key) == 0)
      throw new IllegalArgumentException("Calling decreaseKey() with a key equal to the key in the priority queue");
    if (keys[i].compareTo(key) < 0)
      throw new IllegalArgumentException(
          "Calling decreaseKey() with a key strictly greater than the key in the priority queue");
    keys[i] = key;
    swim(qp[i]);
  }

  public void increaseKey(int i, Key key) {
    validateIndex(i);
    if (!contains(i))
      throw new NoSuchElementException("index is not in the priority queue");
    if (keys[i].compareTo(key) == 0)
      throw new IllegalArgumentException("Calling increaseKey() with a key equal to the key in the priority queue");
    if (keys[i].compareTo(key) > 0)
      throw new IllegalArgumentException(
          "Calling increaseKey() with a key strictly less than the key in the priority queue");
    keys[i] = key;
    sink(qp[i]);
  }

  public void remove(int i) {
    validateIndex(i);
    if (!contains(i))
      throw new NoSuchElementException("index is not in the priority queue");
    int index = qp[i];
    xchg(index, n--);
    swim(index);
    sink(index);
    keys[i] = null;
    qp[i] = -1;
  }

  private void validateIndex(int i) {
    if (i < 0)
      throw new IllegalArgumentException("index is negative: " + i);
    if (i >= maxN)
      throw new IllegalArgumentException("index >= capacity: " + i);
  }

  private boolean greater(int i, int j) {
    return keys[pq[i]].compareTo(keys[pq[j]]) > 0;
  }

  private void xchg(int i, int j) {
    int swap = pq[i];
    pq[i] = pq[j];
    pq[j] = swap;
    qp[pq[i]] = i;
    qp[pq[j]] = j;
  }

  private void swim(int k) {
    while (k > 1 && greater(k / 2, k)) {
      xchg(k, k / 2);
      k = k / 2;
    }
  }

  private void sink(int k) {
    while (2 * k <= n) {
      int j = 2 * k;
      if (j < n && greater(j, j + 1))
        j++;
      if (!greater(k, j))
        break;
      xchg(k, j);
      k = j;
    }
  }

  public Iterator<Integer> iterator() {
    return new HeapIterator();
  }

  private class HeapIterator implements Iterator<Integer> {
    private IndexedMinPQ<Key> copy;

    public HeapIterator() {
      copy = new IndexedMinPQ<Key>(pq.length - 1);
      for (int i = 1; i <= n; i++)
        copy.insert(pq[i], keys[pq[i]]);
    }

    public boolean hasNext() {
      return !copy.isEmpty();
    }

    public void remove() {
      throw new UnsupportedOperationException();
    }

    public Integer next() {
      if (!hasNext())
        throw new NoSuchElementException();
      return copy.removeMin();
    }
  }
}
