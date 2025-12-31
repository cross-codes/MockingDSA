package collections.tuples;

import java.util.Objects;

public class OrderedQuintuplet<A extends Comparable<A>, B extends Comparable<B>, C extends Comparable<C>, D extends Comparable<D>, E extends Comparable<E>>
    implements Comparable<OrderedQuintuplet<A, B, C, D, E>> {

  public A first;
  public B second;
  public C third;
  public D fourth;
  public E fifth;

  public OrderedQuintuplet(A first, B second, C third, D fourth, E fifth) {
    this.first = first;
    this.second = second;
    this.third = third;
    this.fourth = fourth;
    this.fifth = fifth;
  }

  @Override
  public int compareTo(OrderedQuintuplet<A, B, C, D, E> other) {
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

    return this.fifth.compareTo(other.fifth);
  }

  @Override
  @SuppressWarnings("unchecked")
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof OrderedQuintuplet))
      return false;
    OrderedQuintuplet<A, B, C, D, E> other = (OrderedQuintuplet<A, B, C, D, E>) obj;
    return Objects.equals(this.first, other.first)
        && Objects.equals(this.second, other.second)
        && Objects.equals(this.third, other.third)
        && Objects.equals(this.fourth, other.fourth)
        && Objects.equals(this.fifth, other.fifth);
  }

  @Override
  public int hashCode() {
    return Objects.hash(first, second, third, fourth, fifth);
  }
}
