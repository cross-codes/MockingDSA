package collections.tuples.primitive;

import java.util.Objects;

public class LongOrderedPair implements Comparable<LongOrderedPair> {

  public long first;
  public long second;

  public LongOrderedPair(long first, long second) {
    this.first = first;
    this.second = second;
  }

  @Override
  public int compareTo(LongOrderedPair other) {
    int cmp = Long.compare(this.first, other.first);
    if (cmp == 0)
      return Long.compare(this.second, other.second);

    return cmp;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof LongOrderedPair))
      return false;
    LongOrderedPair pair = (LongOrderedPair) obj;
    return this.first == pair.first && this.second == pair.second;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.first, this.second);
  }
}
