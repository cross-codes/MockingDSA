package extras;

import java.util.NoSuchElementException;

public class OptionalLong {
  long value = Long.MIN_VALUE;
  boolean isPresent = false;

  public OptionalLong(long v) {
    this.value = v;
    isPresent = true;
  }

  public OptionalLong() {

  }

  public boolean isPresent() {
    return this.isPresent;
  }

  public long get() throws NoSuchElementException {
    if (!isPresent) {
      throw new NoSuchElementException();
    } else {
      return value;
    }
  }
}
