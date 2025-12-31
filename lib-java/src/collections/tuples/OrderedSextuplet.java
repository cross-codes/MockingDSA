package collections.tuples;

import java.util.Objects;

public class OrderedSextuplet<A extends Comparable<A>, B extends Comparable<B>, C extends Comparable<C>, D extends Comparable<D>, E extends Comparable<E>, F extends Comparable<F>>
    implements Comparable<OrderedSextuplet<A, B, C, D, E, F>> {

  public A first;
  public B second;
  public C third;
  public D fourth;
  public E fifth;
  public F sixth;

  public OrderedSextuplet(A first, B second, C third, D fourth, E fifth, F sixth) {
    this.first = first;
    this.second = second;
    this.third = third;
    this.fourth = fourth;
    this.fifth = fifth;
    this.sixth = sixth;
  }

  @Override
  public int compareTo(OrderedSextuplet<A, B, C, D, E, F> other) {
    int cmp = this.first.compareTo(other.first);
    if (cmp != 0)
      return cmp;

    cmp = this.second.compareTo(other.second);
    if (cmp != 0)
      return cmp;

    cmp = this.third.compareTo(other.third);
    if (cmp != 0)
      return cmp;

    cmp = this.fourth.compareTo(other.fourth);
    if (cmp != 0)
      return cmp;

    cmp = this.fifth.compareTo(other.fifth);
    if (cmp != 0)
      return cmp;

    return this.sixth.compareTo(other.sixth);
  }

  @Override
  @SuppressWarnings("unchecked")
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof OrderedSextuplet))
      return false;
    OrderedSextuplet<A, B, C, D, E, F> other = (OrderedSextuplet<A, B, C, D, E, F>) obj;
    return Objects.equals(this.first, other.first)
        && Objects.equals(this.second, other.second)
        && Objects.equals(this.third, other.third)
        && Objects.equals(this.fourth, other.fourth)
        && Objects.equals(this.fifth, other.fifth)
        && Objects.equals(this.sixth, other.sixth);
  }

  @Override
  public int hashCode() {
    return Objects.hash(first, second, third, fourth, fifth, sixth);
  }
}
