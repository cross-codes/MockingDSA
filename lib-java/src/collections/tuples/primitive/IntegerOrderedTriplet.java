package collections.tuples.primitive;

import java.util.Objects;

public class IntegerOrderedTriplet
    implements Comparable<IntegerOrderedTriplet> {

  public int first;
  public int second;
  public int third;

  public IntegerOrderedTriplet(int first, int second, int third) {
    this.first = first;
    this.second = second;
    this.third = third;
  }

  @Override
  public int compareTo(IntegerOrderedTriplet other) {
    int cmp = Integer.compare(this.first, other.first);
    if (cmp != 0)
      return cmp;

    cmp = Integer.compare(this.second, other.second);
    if (cmp != 0)
      return cmp;

    return Integer.compare(this.third, other.third);
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof IntegerOrderedTriplet))
      return false;
    IntegerOrderedTriplet triplet = (IntegerOrderedTriplet) obj;
    return this.first == triplet.first && this.second == triplet.second
        && this.third == triplet.third;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.first, this.second, this.third);
  }
}
