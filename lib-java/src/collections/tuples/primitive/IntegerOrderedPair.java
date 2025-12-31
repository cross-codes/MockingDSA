package collections.tuples.primitive;

import java.util.Objects;

public class IntegerOrderedPair implements Comparable<IntegerOrderedPair> {

  public int first;
  public int second;

  public IntegerOrderedPair(int first, int second) {
    this.first = first;
    this.second = second;
  }

  @Override
  public int compareTo(IntegerOrderedPair other) {
    int cmp = Integer.compare(this.first, other.first);
    if (cmp == 0)
      return Integer.compare(this.second, other.second);

    return cmp;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof IntegerOrderedPair))
      return false;
    IntegerOrderedPair pair = (IntegerOrderedPair) obj;
    return this.first == pair.first && this.second == pair.second;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.first, this.second);
  }
}
