package collections.tuples;

import java.util.Objects;

public class OrderedTriplet<F extends Comparable<F>, S extends Comparable<S>, T extends Comparable<T>>
    implements Comparable<OrderedTriplet<F, S, T>> {

  public F first;
  public S second;
  public T third;

  public OrderedTriplet(F first, S second, T third) {
    this.first = first;
    this.second = second;
    this.third = third;
  }

  @Override
  public int compareTo(OrderedTriplet<F, S, T> other) {
    int cmp = this.first.compareTo(other.first);
    if (cmp != 0)
      return cmp;

    cmp = this.second.compareTo(other.second);
    if (cmp != 0)
      return cmp;

    return this.third.compareTo(other.third);
  }

  @Override
  @SuppressWarnings("unchecked")
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof OrderedTriplet))
      return false;
    OrderedTriplet<F, S, T> triplet = (OrderedTriplet<F, S, T>) obj;
    return Objects.equals(this.first, triplet.first) && Objects.equals(this.second, triplet.second)
        && Objects.equals(this.third, triplet.third);
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.first, this.second, this.third);
  }
}
