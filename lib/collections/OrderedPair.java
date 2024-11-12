package collections;

import java.util.Objects;

public class OrderedPair<K extends Comparable<K>, V extends Comparable<V>>
    implements Comparable<OrderedPair<K, V>> {
  public K key;
  public V value;

  public OrderedPair(K key, V value) {
    this.key = key;
    this.value = value;
  }

  @Override
  public int compareTo(OrderedPair<K, V> other) {
    int cmp = this.key.compareTo(other.key);
    if (cmp == 0)
      return this.value.compareTo(other.value);
    else
      return cmp;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o)
      return true;
    if (!(o instanceof OrderedPair))
      return false;
    OrderedPair<?, ?> pair = (OrderedPair<?, ?>) o;
    return Objects.equals(this.key, pair.key) && Objects.equals(this.value, pair.value);
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.key, this.value);
  }
}