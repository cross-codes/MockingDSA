package util;

public class BarrettReducer {
  private final long mod;
  private final long m;

  public BarrettReducer(long mod) {
    this.mod = mod;
    this.m = Long.divideUnsigned(-1L, mod);
  }

  public long reduce(long a) {
    long q = unsignedMultiplyHigh(m, a);
    long v = a - (q * mod);
    return Long.compareUnsigned(v, mod) >= 0 ? v - mod : v;
  }

  private static long unsignedMultiplyHigh(long x, long y) {
    long result = Math.multiplyHigh(x, y);
    result += (y & (x >> 63));
    result += (x & (y >> 63));
    return result;
  }
}
