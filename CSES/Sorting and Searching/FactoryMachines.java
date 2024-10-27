public class FactoryMachines {

  public static void main(String[] args) {
    final StandardInputReader in = new StandardInputReader();
    final StandardOutputWriter out = new StandardOutputWriter();
    int n = in.nextInt(), t = in.nextInt();
    int[] arr = in.readIntegerArray(n);

    LongFunction proc = (time) -> {
      long sum = 0;
      for (int e : arr)
        sum += time / e;
      return sum;
    };

    long res = Algebra.binarySearchOnAnswerSpace(proc, t, 1, Array.min(arr) * (long) t);

    out.append(res).appendNewLine();
    out.flush();
  }
}

@FunctionalInterface
interface Procedure {
  void run();
}

@FunctionalInterface
interface LongFunction {
  long apply(long t);
}

class Random {

  private static long seed = System.nanoTime() ^ 8682522807148012L;

  private Random() {
  }

  public static void nextBytes(byte[] bytes) {
    for (int i = 0, len = bytes.length; i < len;) {
      for (int rnd = nextInt(), n = Math.min(len - i, Integer.SIZE / Byte.SIZE); n-- > 0; rnd >>= Byte.SIZE)
        bytes[i++] = (byte) rnd;
    }
  }

  public static int nextInt() {
    return next(32);
  }

  public static int nextInt(int bound) {
    int r = next(31);
    int m = bound - 1;
    if ((bound & m) == 0)
      r = (int) (bound * (long) r >> 31);
    else
      for (int u = r; u - (r = u % bound) + m < 0; u = next(31))
        ;
    return r;
  }

  public static long nextLong() {
    return (long) next(32) << 32 | next(32);
  }

  public static boolean nextBoolean() {
    return next(1) != 0;
  }

  public static float nextFloat() {
    return next(24) / (float) (1 << 24);
  }

  public static double nextDouble() {
    return ((long) next(26) << 27 | next(27)) * 0x1.0p-53;
  }

  private static int next(int bits) {
    seed = seed * 0x5DEECE66DL + 0xBL & 0xFFFFFFFFFFFFL;
    return (int) (seed >>> 48 - bits);
  }
}

class Array {
  private Array() {
  }

  public static void sort(int[] array) {
    int bits = 4;
    int radix = 1 << bits;
    int[][] buckets = new int[radix][array.length];
    int[] size = new int[radix];
    for (int e : array) {
      int index = e & radix - 1;
      buckets[index][size[index]++] = e;
    }
    int[][] newBuckets = new int[radix][array.length];
    for (int i = bits; i < Integer.SIZE; i += bits) {
      int[] newSize = new int[radix];
      for (int j = 0; j < radix; j++) {
        for (int k = 0; k < size[j]; k++) {
          int index = buckets[j][k] >>> i & radix - 1;
          newBuckets[index][newSize[index]++] = buckets[j][k];
        }
      }
      int[][] temp = buckets;
      buckets = newBuckets;
      newBuckets = temp;
      size = newSize;
    }
    {
      int i = 0;
      for (int j = radix >> 1; j < radix; j++) {
        for (int k = 0; k < size[j]; k++)
          array[i++] = buckets[j][k];
      }
      for (int j = 0; j < radix >> 1; j++) {
        for (int k = 0; k < size[j]; k++)
          array[i++] = buckets[j][k];
      }
    }
  }

  public static <T> void shuffle(int[] array) {
    for (int i = array.length; i > 1; i--)
      swap(array, Random.nextInt(i), i - 1);
  }

  public static <T> void shuffle(T[] array) {
    for (int i = array.length; i > 1; i--)
      swap(array, Random.nextInt(i), i - 1);
  }

  public static void swap(byte[] array, int i, int j) {
    byte temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }

  public static void swap(int[] array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }

  public static <T> void swap(T[] array, int i, int j) {
    T temp = array[i];
    array[i] = array[j];
    array[j] = temp;
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
        swap(array, index, length);
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
        swap(array, index, length);
        permute(array, length, procedure);
      }
    }
  }

  public static int min(int[] array) {
    int min = Integer.MAX_VALUE;
    for (int e : array) {
      min = Math.min(min, e);
    }
    return min;
  }

  public static int max(int[] array) {
    int max = Integer.MIN_VALUE;
    for (int e : array) {
      max = Math.max(max, e);
    }
    return max;
  }

  public static long min(long[] array) {
    long min = Long.MAX_VALUE;
    for (long e : array) {
      min = Math.min(e, min);
    }
    return min;
  }

  public static long max(long[] array) {
    long max = Long.MIN_VALUE;
    for (long e : array) {
      max = Math.max(e, max);
    }
    return max;
  }
}

class Algebra {

  private static final double EPSILON = 1E-6;

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

  public static long binarySearchOnAnswerSpace(
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

  public byte nextCharacter() {
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