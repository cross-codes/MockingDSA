import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.Random;

public class _1828B implements Runnable {

  InputStream in;
  StandardOutputWriter out;
  private byte[] inbuf = new byte[1024];
  public int lenbuf = 0, ptrbuf = 0;
  static final Random random = new Random();

  public static void main(String[] args) {
    new Thread(null, new _1828B(), "", 256 * (1L << 20)).start();
  }

  @Override
  public void run() {
    try {
      in = System.in;
      out = new StandardOutputWriter(System.out);
      solve();
      in.close();
      out.flush();
    } catch (Throwable t) {
      t.printStackTrace(System.err);
      System.exit(-1);
    }
  }

  int readByte() {
    if (lenbuf == -1) throw new InputMismatchException();
    if (ptrbuf >= lenbuf) {
      ptrbuf = 0;
      try {
        lenbuf = in.read(inbuf);
      } catch (IOException e) {
        throw new InputMismatchException();
      }
      if (lenbuf <= 0) return -1;
    }
    return inbuf[ptrbuf++];
  }

  boolean isSpaceChar(int c) {
    return !(c >= 33 && c <= 126);
  }

  int skip() {
    int b;
    while ((b = readByte()) != -1 && isSpaceChar(b))
      ;
    return b;
  }

  char rc() {
    return (char) skip();
  }

  String rs() {
    int b = skip();
    StringBuilder sb = new StringBuilder();
    while (!(isSpaceChar(b))) {
      sb.appendCodePoint(b);
      b = readByte();
    }
    return sb.toString();
  }

  char[] rs(int n) {
    char[] buf = new char[n];
    int b = skip(), p = 0;
    while (p < n && !(isSpaceChar(b))) {
      buf[p++] = (char) b;
      b = readByte();
    }
    return n == p ? buf : Arrays.copyOf(buf, p);
  }

  int ri() {
    return (int) rl();
  }

  long rl() {
    long num = 0;
    int b;
    boolean minus = false;
    while ((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-'))
      ;
    if (b == '-') {
      minus = true;
      b = readByte();
    }

    while (true) {
      if (b >= '0' && b <= '9') {
        num = num * 10 + (b - '0');
      } else {
        return minus ? -num : num;
      }
      b = readByte();
    }
  }

  double rd() {
    return Double.parseDouble(rs());
  }

  int[] ra(int n) {
    int[] a = new int[n];
    for (int i = 0; i < n; i++) a[i] = ri();
    return a;
  }

  long[] ral(int n) {
    long[] a = new long[n];
    for (int i = 0; i < n; i++) a[i] = rl();
    return a;
  }

  void solve() throws IOException {
    int t = ri();
    final StringBuilder sb = new StringBuilder(t);
    while (t-- > 0) {
      int n = ri();
      ArrayList<Integer> vec = new ArrayList<>();
      for (int i = 1; i < n + 1; i++) {
        int diff = Math.abs(i - ri());
        if (diff != 0) vec.add(diff);
      }

      if (vec.size() == 0) sb.append("0\n");
      else {
        int k = vec.get(0);
        for (int var : vec) {
          k = Algebra.gcd(k, var);
        }
        sb.append(k).append("\n");
      }
    }
    out.print(sb.toString());
  }

  static class Algebra {
    private static final double EPSILON = 1E-6;

    private Algebra() {}

    public static int modPow(int n, int exponent, int m) {
      long result = 1;
      for (long i = 1, j = n; i <= exponent; i <<= 1, j = j * j % m) {
        if ((i & exponent) != 0) result = result * j % m;
      }
      return (int) result;
    }

    public static int modInverse(int n, int p) {
      return modPow(n, p - 2, p);
    }

    public static int[] modInverses(int n, int p) {
      int[] inverses = new int[n + 1];
      inverses[1] = 1;
      for (int i = 2; i <= n; i++) inverses[i] = (int) ((long) (p - p / i) * inverses[p % i] % p);
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
        if (a == 0) return b;
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
        if (a == 0) return b;
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
      if (D == 0) return new double[Dx == 0 && Dy == 0 ? 1 : 0];
      else return new double[] {Dx / D, Dy / D};
    }

    public static double[] solveQuadratic(double a, double b, double c) {
      double delta = b * b - a * c * 4;
      if (Algebra.equal0(delta)) return new double[] {-b / (a * 2)};
      else if (delta < 0) return new double[0];
      else {
        double a2 = a * 2;
        double x = -b / a2;
        double y = Math.sqrt(delta) / a2;
        return new double[] {x + y, x - y};
      }
    }

    public static void permute(byte[] array, Procedure procedure) {
      permute(array, array.length, procedure);
    }

    private static void permute(byte[] array, int length, Procedure procedure) {
      if (length == 1) procedure.run();
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
      if (length == 1) procedure.run();
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
  }

  interface Procedure {
    void run();
  }

  static class StandardOutputWriter {
    private static final int BUFFER_SIZE = 1 << 16;
    private final byte[] buf = new byte[BUFFER_SIZE];
    private final OutputStream out;
    private int ptr = 0;

    public StandardOutputWriter(OutputStream os) {
      this.out = os;
    }

    public StandardOutputWriter(String path) {
      try {
        this.out = new FileOutputStream(path);
      } catch (FileNotFoundException e) {
        throw new RuntimeException("StandardOutputWriter");
      }
    }

    public StandardOutputWriter write(byte b) {
      this.buf[this.ptr++] = b;
      if (this.ptr == BUFFER_SIZE) innerflush();
      return this;
    }

    public StandardOutputWriter write(char c) {
      return write((byte) c);
    }

    public StandardOutputWriter write(char[] s) {
      for (char c : s) {
        this.buf[this.ptr++] = (byte) c;
        if (this.ptr == BUFFER_SIZE) innerflush();
      }
      return this;
    }

    public StandardOutputWriter write(String s) {
      s.chars()
          .forEach(
              c -> {
                this.buf[this.ptr++] = (byte) c;
                if (this.ptr == BUFFER_SIZE) innerflush();
              });
      return this;
    }

    private static int countDigits(int l) {
      if (l >= 1000000000) return 10;
      if (l >= 100000000) return 9;
      if (l >= 10000000) return 8;
      if (l >= 1000000) return 7;
      if (l >= 100000) return 6;
      if (l >= 10000) return 5;
      if (l >= 1000) return 4;
      if (l >= 100) return 3;
      if (l >= 10) return 2;
      return 1;
    }

    public StandardOutputWriter write(int x) {
      if (x == Integer.MIN_VALUE) {
        return write((long) x);
      }
      if (this.ptr + 12 >= BUFFER_SIZE) innerflush();
      if (x < 0) {
        write((byte) '-');
        x = -x;
      }
      int d = countDigits(x);
      for (int i = this.ptr + d - 1; i >= this.ptr; i--) {
        this.buf[i] = (byte) ('0' + x % 10);
        x /= 10;
      }
      this.ptr += d;
      return this;
    }

    private static int countDigits(long l) {
      if (l >= 1000000000000000000L) return 19;
      if (l >= 100000000000000000L) return 18;
      if (l >= 10000000000000000L) return 17;
      if (l >= 1000000000000000L) return 16;
      if (l >= 100000000000000L) return 15;
      if (l >= 10000000000000L) return 14;
      if (l >= 1000000000000L) return 13;
      if (l >= 100000000000L) return 12;
      if (l >= 10000000000L) return 11;
      if (l >= 1000000000L) return 10;
      if (l >= 100000000L) return 9;
      if (l >= 10000000L) return 8;
      if (l >= 1000000L) return 7;
      if (l >= 100000L) return 6;
      if (l >= 10000L) return 5;
      if (l >= 1000L) return 4;
      if (l >= 100L) return 3;
      if (l >= 10L) return 2;
      return 1;
    }

    public StandardOutputWriter write(long x) {
      if (x == Long.MIN_VALUE) {
        return write("" + x);
      }
      if (this.ptr + 21 >= BUFFER_SIZE) innerflush();
      if (x < 0) {
        write((byte) '-');
        x = -x;
      }
      int d = countDigits(x);
      for (int i = this.ptr + d - 1; i >= this.ptr; i--) {
        this.buf[i] = (byte) ('0' + x % 10);
        x /= 10;
      }
      this.ptr += d;
      return this;
    }

    public StandardOutputWriter write(double x, int precision) {
      if (x < 0) {
        write('-');
        x = -x;
      }
      x += Math.pow(10, -precision) / 2;
      write((long) x).write(".");
      x -= (long) x;
      for (int i = 0; i < precision; i++) {
        x *= 10;
        write((char) ('0' + (int) x));
        x -= (int) x;
      }
      return this;
    }

    public StandardOutputWriter writeln(char c) {
      return write(c).writeln();
    }

    public StandardOutputWriter writeln(int x) {
      return write(x).writeln();
    }

    public StandardOutputWriter writeln(long x) {
      return write(x).writeln();
    }

    public StandardOutputWriter writeln(double x, int precision) {
      return write(x, precision).writeln();
    }

    public StandardOutputWriter write(int... xs) {
      boolean first = true;
      for (int x : xs) {
        if (!first) write(' ');
        first = false;
        write(x);
      }
      return this;
    }

    public StandardOutputWriter write(long... xs) {
      boolean first = true;
      for (long x : xs) {
        if (!first) write(' ');
        first = false;
        write(x);
      }
      return this;
    }

    public StandardOutputWriter writeln() {
      return write((byte) '\n');
    }

    public StandardOutputWriter writeln(int... xs) {
      return write(xs).writeln();
    }

    public StandardOutputWriter writeln(long... xs) {
      return write(xs).writeln();
    }

    public StandardOutputWriter writeln(char[] line) {
      return write(line).writeln();
    }

    public StandardOutputWriter writeln(char[]... map) {
      for (char[] line : map) write(line).writeln();
      return this;
    }

    public StandardOutputWriter writeln(String s) {
      return write(s).writeln();
    }

    private void innerflush() {
      try {
        this.out.write(this.buf, 0, this.ptr);
        this.ptr = 0;
      } catch (IOException e) {
        throw new RuntimeException("innerflush");
      }
    }

    public void flush() {
      innerflush();
      try {
        this.out.flush();
      } catch (IOException e) {
        throw new RuntimeException("flush");
      }
    }

    public StandardOutputWriter print(byte b) {
      return write(b);
    }

    public StandardOutputWriter print(char c) {
      return write(c);
    }

    public StandardOutputWriter print(char[] s) {
      return write(s);
    }

    public StandardOutputWriter print(String s) {
      return write(s);
    }

    public StandardOutputWriter print(int x) {
      return write(x);
    }

    public StandardOutputWriter print(long x) {
      return write(x);
    }

    public StandardOutputWriter print(double x, int precision) {
      return write(x, precision);
    }

    public StandardOutputWriter println(char c) {
      return writeln(c);
    }

    public StandardOutputWriter println(int x) {
      return writeln(x);
    }

    public StandardOutputWriter println(long x) {
      return writeln(x);
    }

    public StandardOutputWriter println(double x, int precision) {
      return writeln(x, precision);
    }

    public StandardOutputWriter print(int... xs) {
      return write(xs);
    }

    public StandardOutputWriter print(long... xs) {
      return write(xs);
    }

    public StandardOutputWriter println(int... xs) {
      return writeln(xs);
    }

    public StandardOutputWriter println(long... xs) {
      return writeln(xs);
    }

    public StandardOutputWriter println(char[] line) {
      return writeln(line);
    }

    public StandardOutputWriter println(char[]... map) {
      return writeln(map);
    }

    public StandardOutputWriter println(String s) {
      return writeln(s);
    }

    public StandardOutputWriter println() {
      return writeln();
    }
  }
}
