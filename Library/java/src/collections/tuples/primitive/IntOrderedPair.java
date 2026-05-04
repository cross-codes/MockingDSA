package collections.tuples.primitive;

import java.util.Objects;

public class IntOrderedPair implements Comparable<IntOrderedPair> {

  public int first;
  public int second;

  public IntOrderedPair(int first, int second) {
    this.first = first;
    this.second = second;
  }

  @Override
  public int compareTo(IntOrderedPair other) {
    int cmp = Integer.compare(this.first, other.first);
    if (cmp == 0)
      return Integer.compare(this.second, other.second);

    return cmp;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof IntOrderedPair))
      return false;
    IntOrderedPair pair = (IntOrderedPair) obj;
    return this.first == pair.first && this.second == pair.second;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.first, this.second);
  }
}
