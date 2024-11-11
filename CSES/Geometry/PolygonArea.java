import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.util.Arrays;

@Launchable(author = "Cross", judge = "CSES")
public class PolygonArea extends ModuleSignatures implements Debug, Runnable {

  private final StandardInputReader in = new StandardInputReader();
  private final StandardOutputWriter out = new StandardOutputWriter();

  @Override
  public void run() {
    this.consolidateOutput();
    this.out.flush();
  }

  public static void main(String... args) {
    new Thread(null, new PolygonArea(), "LaunchableDriver", 1048576).start();
  }

  private void consolidateOutput() {
    int n = in.nextInt();
    long area = 0L;

    TwoDimensionalVector first = new TwoDimensionalVector(in.nextInt(), in.nextInt());
    TwoDimensionalVector prev = first;

    for (int i = 1; i < n; i++) {
      TwoDimensionalVector vector = new TwoDimensionalVector(in.nextInt(), in.nextInt());
      area += prev.cross(vector);
      prev = vector;
    }

    area += prev.cross(first);
    out.append(Math.abs(area)).appendNewLine();
  }

}

@MultipleInheritanceDisallowed(inheritor = "PolygonArea")
abstract strictfp class ModuleSignatures {
}

class TwoDimensionalVector {
  private final int x;
  private final int y;

  public TwoDimensionalVector(int x, int y) {
    this.x = x;
    this.y = y;
  }

  public long cross(TwoDimensionalVector vector) {
    return (long) this.x * vector.y - (long) this.y * vector.x;
  }

  public long dot(TwoDimensionalVector vector) {
    return (long) this.x * vector.x + (long) this.y * vector.y;
  }

  public double norm() {
    return Math.sqrt(this.x * this.x + this.y * this.y);
  }

  public TwoDimensionalVector add(TwoDimensionalVector vector) {
    return new TwoDimensionalVector(this.x + vector.x, this.y + vector.y);
  }

  public TwoDimensionalVector subtract(TwoDimensionalVector vector) {
    return new TwoDimensionalVector(this.x - vector.x, this.y - vector.y);
  }

  public TwoDimensionalVector perpendicularVector() {
    return new TwoDimensionalVector(-this.y, this.x);
  }

  public double angleBetween(TwoDimensionalVector vector) {
    double dotProduct = this.dot(vector);
    double normProduct = this.norm() * vector.norm();
    if (normProduct == 0)
      return (dotProduct < 0D) ? Double.NEGATIVE_INFINITY : Double.POSITIVE_INFINITY;
    return Math.acos(dotProduct / normProduct);
  }

  public double angle() {
    if (this.x == 0)
      return this.y > 0 ? Double.POSITIVE_INFINITY : Double.NEGATIVE_INFINITY;
    return Math.atan2(this.y, this.x);
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (obj == null || !(obj instanceof TwoDimensionalVector))
      return false;

    TwoDimensionalVector vector = (TwoDimensionalVector) obj;
    return this.x == vector.x && this.y == vector.y;
  }

  @Override
  public String toString() {
    return "<" + this.x + ", " + this.y + ">";
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

interface Debug {
  public final boolean isLocal = getLocal();

  public static boolean getLocal() {
    try {
      return System.getProperty("CROSS_DEBUG") != null;
    } catch (SecurityException ex) {
      return false;
    }
  }

  public static <T> String convStr(T t) {
    if (t == null)
      return "null";
    if (t instanceof Iterable)
      return convStr((Iterable<?>) t);
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
      return convStr((Object[]) t);
    return t.toString();
  }

  public static <T> String convStr(T[] arr) {
    StringBuilder ret = new StringBuilder();
    ret.append("{");
    boolean first = true;
    for (T t : arr) {
      if (!first)
        ret.append(", ");
      first = false;
      ret.append(convStr(t));
    }
    ret.append("}");
    return ret.toString();
  }

  public static <T> String convStr(Iterable<T> iter) {
    StringBuilder ret = new StringBuilder();
    ret.append("{");
    boolean first = true;
    for (T t : iter) {
      if (!first)
        ret.append(", ");
      first = false;
      ret.append(convStr(t));
    }
    ret.append("}");
    return ret.toString();
  }

  public static void print(Object... __VA_ARGS__) {
    if (isLocal) {
      System.err.print("Line #" + Thread.currentThread().getStackTrace()[2].getLineNumber() + ": [");
      for (int i = 0; i < __VA_ARGS__.length; i++) {
        if (i != 0)
          System.err.print(", ");
        System.err.print(convStr(__VA_ARGS__[i]));
      }
      System.err.println("]");
    }
  }
}

@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.TYPE)
@interface Launchable {
  String author();

  String judge();
}

@Retention(RetentionPolicy.SOURCE)
@Target(ElementType.TYPE)
@interface MultipleInheritanceDisallowed {
  String inheritor();
}

@FunctionalInterface
interface Procedure {
  void run();
}

@FunctionalInterface
interface LongFunction {
  long apply(long t);
}