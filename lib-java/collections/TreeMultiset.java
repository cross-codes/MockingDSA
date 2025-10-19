import java.util.Comparator;
import java.util.TreeMap;

public class TreeMultiset<E> {

  public TreeMap<E, Integer> map;
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
    this.map.put(e, this.map.getOrDefault(e, 0) + 1);
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

  @SuppressWarnings("unchecked")
  @Override
  public Object clone() throws CloneNotSupportedException {
    TreeMultiset<E> cloned = (TreeMultiset<E>) super.clone();
    cloned.map = new TreeMap<>(this.map);
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
}
