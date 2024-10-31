public class _1474B {

  private static int nextPrime(int d) {
    if (d <= 2)
      return 2;
    int prime = d;
    boolean found = false;
    while (!found) {
      if (isPrime(prime)) {
        found = true;
        break;
      }
      prime++;
    }
    return prime;
  }

  private static boolean isPrime(int n) {
    if (n <= 1)
      return false;
    if (n <= 3)
      return true;
    if (n % 2 == 0 || n % 3 == 0)
      return false;

    for (int i = 5; i * i <= n; i = i + 6)
      if (n % i == 0 || n % (i + 2) == 0)
        return false;
    return true;
  }

  public static void main(String[] args) {
    final StandardInputReader in = new StandardInputReader();
    final StandardOutputWriter out = new StandardOutputWriter();

    int t = in.nextInt();
    while (t-- > 0) {
      int d = in.nextInt();
      int a = nextPrime(d + 1);
      int b = nextPrime(a + d);
      out.append((long) a * b).appendNewLine();
    }

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