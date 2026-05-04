import java.util.Arrays;
import java.util.Comparator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.function.IntPredicate;

class Solution {
  public int minimizeMax(int[] nums, int p) {
    if (p == 0) {
      return 0;
    }

    Arrays.sort(nums);
    TreeMultiset<Integer> set = new TreeMultiset<>();
    for (int e : nums) {
      set.add(e);
    }

    IntPredicate pred = (M) -> {
      var ws = set.clone();
      int sz = 0;
      for (int e : nums) {
        if (!ws.contains(e)) {
          continue;
        }

        ws.removeOne(e);

        Integer fkc = ws.ceiling(e);
        if (fkc != null && (fkc - e) <= M) {
          sz += 1;
          ws.removeOne(fkc);
        } else {
          ws.add(e);
        }
      }

      return sz >= p;
    };

    int L = -1, R = (int) 2e8 + 1;
    while (R - L > 1) {
      int M = L + ((R - L) >>> 1);
      if (pred.test(M)) {
        R = M;
      } else {
        L = M;
      }
    }

    var ws = set.clone();
    int mxd = Integer.MIN_VALUE;
    for (int e : nums) {
      if (!ws.contains(e)) {
        continue;
      }

      ws.removeOne(e);

      Integer fkc = ws.ceiling(e);
      if (fkc != null && (fkc - e) <= R) {
        mxd = Math.max(fkc - e, mxd);
        ws.removeOne(fkc);
      } else {
        ws.add(e);
      }
    }

    return (mxd == Integer.MIN_VALUE) ? (int) 1e9 : mxd;
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
