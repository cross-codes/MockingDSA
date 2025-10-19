package collections;

import java.util.Objects;

public class OrderedPair<F extends Comparable<F>, S extends Comparable<S>>
    implements Comparable<OrderedPair<F, S>> {

  public F first;
  public S second;

  public OrderedPair(F first, S second) {
    this.first = first;
    this.second = second;
  }

  @Override
  public int compareTo(OrderedPair<F, S> other) {
    int cmp = this.first.compareTo(other.first);
    if (cmp == 0)
      return this.second.compareTo(other.second);
    else
      return cmp;
  }

  @Override
  @SuppressWarnings("unchecked")
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof OrderedPair))
      return false;
    OrderedPair<F, S> pair = (OrderedPair<F, S>) obj;
    return Objects.equals(this.first, pair.first) && Objects.equals(this.second, pair.second);
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.first, this.second);
  }
}
