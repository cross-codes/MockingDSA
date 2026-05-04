import java.util.Arrays;

@Launchable(author = "Evermore", hostname = "probook", judge = "CSES")
public class BinomialCoefficients extends ModuleSignatures implements Runnable {

  private final StandardInputReader in = new StandardInputReader();
  private final StandardOutputWriter out = new StandardOutputWriter();
  @SuppressWarnings("unused")
  private final Debug dbg = Debug.getInstance();

  @Override
  public void run() {
    int t = 1;
    for (int _case = 1; _case <= t; _case++)
      this.solveCase(_case);
    this.out.flush();
  }

  public static void main(String... args) {
    new Thread(null, new BinomialCoefficients(), "LaunchableDriver", 1048576L).start();
  }

  private void solveCase(int _case) {
    final int MOD = 1000000007;
    int n = in.nextInt();
    int[] factorial = new int[1000001], inverseFactorial = new int[1000001];
    factorial[0] = inverseFactorial[0] = 1;

    for (int i = 1; i < 1000001; i++) {
      factorial[i] = Math.floorMod((long) i * factorial[i - 1], MOD);
      inverseFactorial[i] = Algebra.modInverse(factorial[i], MOD);
    }

    for (int i = 0; i < n; i++) {
      int a = in.nextInt(), b = in.nextInt();
      int res = Math.floorMod(
          Math.floorMod(factorial[a] * (long) inverseFactorial[b], MOD) * (long) inverseFactorial[a - b], MOD);
      out.append(res).appendNewLine();
    }
  }

}

@MultipleInheritanceDisallowed(inheritor = BinomialCoefficients.class)
abstract class ModuleSignatures {
}

@FunctionalInterface
interface Procedure {
  void run();
}

@FunctionalInterface
interface LongFunction {
  long apply(long t);
}

final class Algebra {

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

  public static boolean solveDiophantine(int a, int b, int c, int[] xyg) {
    int[] xy = { xyg[0], xyg[1] };
    xyg[2] = exGCD(Math.abs(a), Math.abs(b), xy);
    if (c % xyg[2] != 0) {
      return false;
    }

    xyg[0] *= c / xyg[2];
    xyg[1] *= c / xyg[2];
    if (a < 0) {
      xyg[0] = -xyg[0];
    }

    if (b < 0) {
      xyg[1] = -xyg[1];
    }

    return true;
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

  private static int exGCD(int a, int b, int[] xy) {
    if (b == 0) {
      xy[0] = 1;
      xy[1] = 0;
      return a;
    }

    int d = exGCD(b, a % b, xy);
    int x1 = xy[0];
    int y1 = xy[1];

    xy[0] = y1;
    xy[1] = x1 - y1 * (a / b);

    return d;
  }

  @Override
  protected Object clone() throws CloneNotSupportedException {
    throw new CloneNotSupportedException();
  }
}

class StandardInputReader {

  private final byte[] buffer;
  private int pos;

  public StandardInputReader() {
    try {
      this.pos = 0;
      this.buffer = new byte[System.in.available() + 1];
      this.buffer[this.buffer.length - 1] = '\n';
      System.in.read(this.buffer);
    } catch (Exception ex) {
      throw new RuntimeException(ex);
    }
  }

  public byte[] next(int n) {
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b != '\n' && b != '\r') {
        this.pos--;
        break;
      }
    }
    byte[] bytes = new byte[n];
    System.arraycopy(buffer, this.pos, bytes, 0, n);
    this.pos += n;
    return bytes;
  }

  public byte[] next() {
    int from;
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b != ' ' && b != '\n' && b != '\r') {
        from = this.pos;
        break;
      }
    }
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b == ' ' || b == '\n' || b == '\r')
        break;
    }
    byte[] bytes = new byte[this.pos - from];
    System.arraycopy(this.buffer, from - 1, bytes, 0, bytes.length);
    return bytes;
  }

  public byte[] nextLine() {
    int from = this.pos;
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b == '\n' || b == '\r') {
        if (b == '\r' && this.buffer[this.pos] == '\n')
          this.pos++;
        break;
      }
    }
    byte[] bytes = new byte[this.pos - from - 1];
    System.arraycopy(this.buffer, from, bytes, 0, bytes.length);
    return bytes;
  }

  public byte nextByte() {
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b != ' ' && b != '\n' && b != '\r')
        return b;
    }
  }

  public int nextInt() {
    int n;
    boolean positive;
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b == '-') {
        positive = false;
        n = this.buffer[this.pos++] - '0';
        break;
      } else if (b >= '0' && b <= '9') {
        positive = true;
        n = b - '0';
        break;
      }
    }
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b >= '0' && b <= '9')
        n = n * 10 + b - '0';
      else
        return positive ? n : -n;
    }
  }

  public long nextLong() {
    long n;
    boolean positive;
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b == '-') {
        positive = false;
        n = this.buffer[this.pos++] - '0';
        break;
      } else if (b >= '0' && b <= '9') {
        positive = true;
        n = b - '0';
        break;
      }
    }
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b >= '0' && b <= '9')
        n = n * 10 + b - '0';
      else
        return positive ? n : -n;
    }
  }

  public double nextDouble() {
    long n;
    boolean positive;
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b == '-') {
        positive = false;
        n = this.buffer[this.pos++] - '0';
        break;
      } else if (b >= '0' && b <= '9') {
        positive = true;
        n = b - '0';
        break;
      }
    }
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b >= '0' && b <= '9')
        n = n * 10 + b - '0';
      else if (b == '.')
        break;
      else
        return positive ? n : -n;
    }
    long m = 0;
    long o = 1;
    while (true) {
      byte b = this.buffer[this.pos++];
      if (b >= '0' && b <= '9') {
        m = m * 10 + b - '0';
        o *= 10;
      } else {
        double d = n + (double) m / o;
        return positive ? d : -d;
      }
    }
  }

  public int[] readIntegerArray(int n) {
    int[] a = new int[n];
    for (int i = 0; i < n; i++)
      a[i] = nextInt();
    return a;
  }

  public long[] readLongArray(int n) {
    long[] a = new long[n];
    for (int i = 0; i < n; i++)
      a[i] = nextLong();
    return a;
  }

  public boolean hasNextByte() {
    return this.pos < this.buffer.length - 1;
  }
}

class StandardOutputWriter {

  private static final int BUFFER_SIZE = 1048576;
  private final byte[] buffer;
  private int pos;

  public StandardOutputWriter() {
    this.pos = 0;
    this.buffer = new byte[BUFFER_SIZE];
  }

  public StandardOutputWriter append(String s) {
    int length = s.length();
    this.ensureCapacity(length);
    for (int i = 0; i < length; i++)
      this.buffer[this.pos++] = (byte) s.charAt(i);
    return this;
  }

  public StandardOutputWriter append(byte[] bytes) {
    if (BUFFER_SIZE - this.pos < bytes.length) {
      this.flush();
      if (bytes.length > BUFFER_SIZE) {
        System.out.write(bytes, 0, bytes.length);
        return this;
      }
    }
    for (byte b : bytes)
      this.buffer[this.pos++] = b;
    return this;
  }

  public StandardOutputWriter append(byte[] bytes, int from, int to) {
    int length = to - from;
    if (BUFFER_SIZE - this.pos < length) {
      this.flush();
      if (length > BUFFER_SIZE) {
        System.out.write(bytes, from, length);
        return this;
      }
    }
    for (int i = from; i < to; i++)
      this.buffer[this.pos++] = bytes[i];
    return this;
  }

  public StandardOutputWriter append(char c) {
    this.ensureCapacity(1);
    this.buffer[this.pos++] = (byte) c;
    return this;
  }

  public StandardOutputWriter append(int i) {
    return this.append(Integer.toString(i));
  }

  public StandardOutputWriter append(long l) {
    return this.append(Long.toString(l));
  }

  public StandardOutputWriter append(double d) {
    return this.append(Double.toString(d));
  }

  public StandardOutputWriter appendAll(Object... varargs) {
    for (Object obj : varargs)
      this.append(obj != null ? obj.toString() : "null");
    return this;
  }

  public void appendNewLine() {
    this.ensureCapacity(1);
    this.buffer[this.pos++] = '\n';
  }

  public void flush() {
    System.out.write(this.buffer, 0, this.pos);
    this.pos = 0;
  }

  private void ensureCapacity(int n) {
    if (BUFFER_SIZE - this.pos < n)
      this.flush();
  }
}

@Singleton
final class Debug {

  private boolean local;
  private static Debug instance;

  private Debug() {
    try {
      if (System.getProperty("EVERMORE") != null)
        this.local = true;
    } catch (SecurityException ex) {
      this.local = false;
    }
  }

  public static Debug getInstance() {
    if (instance == null)
      instance = new Debug();

    return instance;
  }

  private <T> String getStringRepresentation(T t) {
    if (t == null)
      return "null";
    if (t instanceof Iterable)
      return getStringRepresentation((Iterable<?>) t);
    else if (t instanceof int[]) {
      String s = Arrays.toString((int[]) t);
      return "{" + s.substring(1, s.length() - 1) + "}";
    } else if (t instanceof long[]) {
      String s = Arrays.toString((long[]) t);
      return "{" + s.substring(1, s.length() - 1) + "}";
    } else if (t instanceof char[]) {
      String s = Arrays.toString((char[]) t);
      return "{" + s.substring(1, s.length() - 1) + "}";
    } else if (t instanceof double[]) {
      String s = Arrays.toString((double[]) t);
      return "{" + s.substring(1, s.length() - 1) + "}";
    } else if (t instanceof boolean[]) {
      String s = Arrays.toString((boolean[]) t);
      return "{" + s.substring(1, s.length() - 1) + "}";
    } else if (t instanceof Object[])
      return getStringRepresentation((Object[]) t);
    return t.toString();
  }

  private <T> String getStringRepresentation(T[] arr) {
    StringBuilder ret = new StringBuilder();
    ret.append("{");
    boolean first = true;
    for (T t : arr) {
      if (!first)
        ret.append(", ");
      first = false;
      ret.append(getStringRepresentation(t));
    }
    ret.append("}");
    return ret.toString();
  }

  private <T> String getStringRepresentation(Iterable<T> iter) {
    StringBuilder ret = new StringBuilder();
    ret.append("{");
    boolean first = true;
    for (T t : iter) {
      if (!first)
        ret.append(", ");
      first = false;
      ret.append(getStringRepresentation(t));
    }
    ret.append("}");
    return ret.toString();
  }

  public void print(Object... __VA_ARGS__) {
    if (this.local) {
      System.err.print("Line #" + Thread.currentThread().getStackTrace()[2]
          .getLineNumber() + ": [");
      for (int i = 0; i < __VA_ARGS__.length; i++) {
        if (i != 0)
          System.err.print(", ");
        System.err.print(getStringRepresentation(__VA_ARGS__[i]));
      }
      System.err.println("]");
    }
  }

  @Override
  protected Object clone() throws CloneNotSupportedException {
    throw new CloneNotSupportedException();
  }
}

@java.lang.annotation.Retention(java.lang.annotation.RetentionPolicy.RUNTIME)
@java.lang.annotation.Target(java.lang.annotation.ElementType.TYPE)
@interface Launchable {
  String author();

  String hostname();

  String judge();
}

@java.lang.annotation.Retention(java.lang.annotation.RetentionPolicy.SOURCE)
@java.lang.annotation.Target(java.lang.annotation.ElementType.TYPE)
@interface MultipleInheritanceDisallowed {
  Class<?> inheritor();
}

@java.lang.annotation.Retention(java.lang.annotation.RetentionPolicy.RUNTIME)
@java.lang.annotation.Target(java.lang.annotation.ElementType.TYPE)
@interface Singleton {
}
