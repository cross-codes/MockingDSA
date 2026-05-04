package collections.tuples;

import java.util.Objects;

public class OrderedQuadruplet<A extends Comparable<A>, B extends Comparable<B>, C extends Comparable<C>, D extends Comparable<D>>
    implements Comparable<OrderedQuadruplet<A, B, C, D>> {

  public A first;
  public B second;
  public C third;
  public D fourth;

  public OrderedQuadruplet(A first, B second, C third, D fourth) {
    this.first = first;
    this.second = second;
    this.third = third;
    this.fourth = fourth;
  }

  @Override
  public int compareTo(OrderedQuadruplet<A, B, C, D> other) {
    int cmp = this.first.compareTo(other.first);
    if (cmp != 0)
      return cmp;

    cmp = this.second.compareTo(other.second);
    if (cmp != 0)
      return cmp;

    cmp = this.third.compareTo(other.third);
    if (cmp != 0)
      return cmp;

    return this.fourth.compareTo(other.fourth);
  }

  @Override
  @SuppressWarnings("unchecked")
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof OrderedQuadruplet))
      return false;
    OrderedQuadruplet<A, B, C, D> other = (OrderedQuadruplet<A, B, C, D>) obj;
    return Objects.equals(this.first, other.first)
        && Objects.equals(this.second, other.second)
        && Objects.equals(this.third, other.third)
        && Objects.equals(this.fourth, other.fourth);
  }

  @Override
  public int hashCode() {
    return Objects.hash(first, second, third, fourth);
  }
}
