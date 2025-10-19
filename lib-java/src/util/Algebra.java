package util;

public final class Algebra {

  private static final double EPSILON = 1E-6;
  private static final int SIEVE_30 = ~((1 << 1) | (1 << 7) | (1 << 11)
      | (1 << 13) | (1 << 17) | (1 << 19) | (1 << 23) | (1 << 29));
  private static final long FLOOR_SQRT_MAX_LONG = 3037000499L;

  private Algebra() {
  }

  public static int modPow(int n, int exponent, int m) {
    long result = 1;
    for (long i = 1, j = n; i <= exponent; i <<= 1, j = j * j % m) {
      if ((i & exponent) != 0)
        result = result * j % m;
    }
    return (int) result;
  }

  public static int modInverse(int n, int p) {
    return modPow(n, p - 2, p);
  }

  public static int[] modInverses(int n, int p) {
    int[] inverses = new int[n + 1];
    inverses[1] = 1;
    for (int i = 2; i <= n; i++)
      inverses[i] = (int) ((long) (p - p / i) * inverses[p % i] % p);
    return inverses;
  }

  public static int gcd(int a, int b) {
    if (a < b) {
      int temp = a;
      a = b;
      b = temp;
    }
    while (true) {
      a %= b;
      if (a == 0)
        return b;
      else {
        int temp = a;
        a = b;
        b = temp;
      }
    }
  }

  public static long gcd(long a, long b) {
    if (a < b) {
      long temp = a;
      a = b;
      b = temp;
    }
    while (true) {
      a %= b;
      if (a == 0)
        return b;
      else {
        long temp = a;
        a = b;
        b = temp;
      }
    }
  }

  public static int log2(int n) {
    return 31 - Integer.numberOfLeadingZeros(n);
  }

  public static int ceilLog2(int n) {
    return 32 - Integer.numberOfLeadingZeros(n - 1);
  }

  public static boolean equal(double a, double b) {
    return Math.abs(a - b) < EPSILON;
  }

  public static boolean equal0(double a) {
    return Math.abs(a) < EPSILON;
  }

  public static double[] solveLinear(double a, double b, double c, double d, double e, double f) {
    double D = a * e - b * d;
    double Dx = c * e - b * f;
    double Dy = a * f - c * d;
    if (D == 0)
      return new double[Dx == 0 && Dy == 0 ? 1 : 0];
    else
      return new double[] { Dx / D, Dy / D };
  }

  public static double[] solveQuadratic(double a, double b, double c) {
    double delta = b * b - a * c * 4;
    if (Algebra.equal0(delta))
      return new double[] { -b / (a * 2) };
    else if (delta < 0)
      return new double[0];
    else {
      double a2 = a * 2;
      double x = -b / a2;
      double y = Math.sqrt(delta) / a2;
      return new double[] { x + y, x - y };
    }
  }

  public static void permute(byte[] array, Procedure procedure) {
    permute(array, array.length, procedure);
  }

  private static void permute(byte[] array, int length, Procedure procedure) {
    if (length == 1)
      procedure.run();
    else {
      permute(array, --length, procedure);
      for (int i = 0; i < length; i++) {
        int index = (length & 1) == 0 ? 0 : i;
        byte temp = array[index];
        array[index] = array[length];
        array[length] = temp;
        permute(array, length, procedure);
      }
    }
  }

  public static void permute(int[] array, Procedure procedure) {
    permute(array, array.length, procedure);
  }

  private static void permute(int[] array, int length, Procedure procedure) {
    if (length == 1)
      procedure.run();
    else {
      permute(array, --length, procedure);
      for (int i = 0; i < length; i++) {
        int index = (length & 1) == 0 ? 0 : i;
        int temp = array[index];
        array[index] = array[length];
        array[length] = temp;
        permute(array, length, procedure);
      }
    }
  }

  private static long flip(long a) {
    return a ^ Long.MIN_VALUE;
  }

  public static int compare(long a, long b) {
    return Long.compare(flip(a), flip(b));
  }

  public static long remainder(long dividend, long divisor) {
    if (divisor < 0) {
      if (compare(dividend, divisor) < 0) {
        return dividend;
      } else {
        return dividend - divisor;
      }
    }

    if (dividend >= 0) {
      return dividend % divisor;
    }
    long quotient = ((dividend >>> 1) / divisor) << 1;
    long rem = dividend - quotient * divisor;
    return rem - (compare(rem, divisor) >= 0 ? divisor : 0);
  }

  public static long monotonicBinarySearch(
      LongFunction function, long target, long lowerBound, long upperBound) {
    while (lowerBound < upperBound) {
      long mid = lowerBound + upperBound >> 1;
      long result = function.apply(mid);
      if (result < target)
        lowerBound = mid + 1;
      else
        upperBound = mid;
    }
    return lowerBound;
  }

  public static boolean isPrime(long n) {
    if (n < 2) {
      return false;
    }
    if (n < 66) {
      long mask = (1L << (2 - 2))
          | (1L << (3 - 2))
          | (1L << (5 - 2))
          | (1L << (7 - 2))
          | (1L << (11 - 2))
          | (1L << (13 - 2))
          | (1L << (17 - 2))
          | (1L << (19 - 2))
          | (1L << (23 - 2))
          | (1L << (29 - 2))
          | (1L << (31 - 2))
          | (1L << (37 - 2))
          | (1L << (41 - 2))
          | (1L << (43 - 2))
          | (1L << (47 - 2))
          | (1L << (53 - 2))
          | (1L << (59 - 2))
          | (1L << (61 - 2));
      return ((mask >> ((int) n - 2)) & 1) != 0;
    }

    if ((SIEVE_30 & (1 << (n % 30))) != 0) {
      return false;
    }
    if (n % 7 == 0 || n % 11 == 0 || n % 13 == 0) {
      return false;
    }
    if (n < 17 * 17) {
      return true;
    }

    for (long[] baseSet : millerRabinBaseSets) {
      if (n <= baseSet[0]) {
        for (int i = 1; i < baseSet.length; i++) {
          if (!MillerRabinTester.test(baseSet[i], n)) {
            return false;
          }
        }
        return true;
      }
    }
    throw new AssertionError();
  }

  private static final long[][] millerRabinBaseSets = {
      { 291830, 126401071349994536L },
      { 885594168, 725270293939359937L, 3569819667048198375L },
      { 273919523040L, 15, 7363882082L, 992620450144556L },
      { 47636622961200L, 2, 2570940, 211991001, 3749873356L },
      {
          7999252175582850L,
          2,
          4130806001517L,
          149795463772692060L,
          186635894390467037L,
          3967304179347715805L
      },
      {
          585226005592931976L,
          2,
          123635709730000L,
          9233062284813009L,
          43835965440333360L,
          761179012939631437L,
          1263739024124850375L
      },
      { Long.MAX_VALUE, 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }
  };

  private enum MillerRabinTester {
    SMALL {
      @Override
      long mulMod(long a, long b, long m) {
        return (a * b) % m;
      }

      @Override
      long squareMod(long a, long m) {
        return (a * a) % m;
      }
    },
    LARGE {
      private long plusMod(long a, long b, long m) {
        return (a >= m - b) ? (a + b - m) : (a + b);
      }

      private long times2ToThe32Mod(long a, long m) {
        int remainingPowersOf2 = 32;
        do {
          int shift = Math.min(remainingPowersOf2, Long.numberOfLeadingZeros(a));
          a = remainder(a << shift, m);
          remainingPowersOf2 -= shift;
        } while (remainingPowersOf2 > 0);
        return a;
      }

      @Override
      long mulMod(long a, long b, long m) {
        long aHi = a >>> 32;
        long bHi = b >>> 32;
        long aLo = a & 0xFFFFFFFFL;
        long bLo = b & 0xFFFFFFFFL;
        long result = times2ToThe32Mod(aHi * bHi, m);
        result += aHi * bLo;
        if (result < 0) {
          result = remainder(result, m);
        }
        result += aLo * bHi;
        result = times2ToThe32Mod(result, m);
        return plusMod(result, remainder(aLo * bLo, m), m);
      }

      @Override
      long squareMod(long a, long m) {
        long aHi = a >>> 32;
        long aLo = a & 0xFFFFFFFFL;
        long result = times2ToThe32Mod(aHi * aHi /* < 2^62 */, m);
        long hiLo = aHi * aLo * 2;
        if (hiLo < 0) {
          hiLo = remainder(hiLo, m);
        }
        result += hiLo;
        result = times2ToThe32Mod(result, m);
        return plusMod(result, remainder(aLo * aLo, m), m);
      }
    };

    static boolean test(long base, long n) {
      return ((n <= FLOOR_SQRT_MAX_LONG) ? SMALL : LARGE).testWitness(base, n);
    }

    abstract long mulMod(long a, long b, long m);

    abstract long squareMod(long a, long m);

    private long powMod(long a, long p, long m) {
      long res = 1;
      for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
          res = mulMod(res, a, m);
        }
        a = squareMod(a, m);
      }
      return res;
    }

    private boolean testWitness(long base, long n) {
      int r = Long.numberOfTrailingZeros(n - 1);
      long d = (n - 1) >> r;
      base %= n;
      if (base == 0) {
        return true;
      }
      long a = powMod(base, d, n);
      if (a == 1) {
        return true;
      }
      int j = 0;
      while (a != n - 1) {
        if (++j == r) {
          return false;
        }
        a = squareMod(a, n);
      }
      return true;
    }
  }

  @Override
  protected Object clone() throws CloneNotSupportedException {
    throw new CloneNotSupportedException();
  }
}
