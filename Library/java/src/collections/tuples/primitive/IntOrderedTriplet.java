package collections.tuples.primitive;

import java.util.Objects;

public class IntOrderedTriplet
    implements Comparable<IntOrderedTriplet> {

  public int first;
  public int second;
  public int third;

  public IntOrderedTriplet(int first, int second, int third) {
    this.first = first;
    this.second = second;
    this.third = third;
  }

  @Override
  public int compareTo(IntOrderedTriplet other) {
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
    if (!(obj instanceof IntOrderedTriplet))
      return false;
    IntOrderedTriplet triplet = (IntOrderedTriplet) obj;
    return this.first == triplet.first && this.second == triplet.second
        && this.third == triplet.third;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.first, this.second, this.third);
  }
}
