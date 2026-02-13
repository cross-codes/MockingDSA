import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;
import java.util.PriorityQueue;

@Launchable(author = "Evermore", hostname = "probook", judge = "CSES")
public class FlightDiscount extends ModuleSignatures implements Runnable {

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
    new Thread(null, new FlightDiscount(), "LaunchableDriver", 1048576L).start();
  }

  private void solveCase(int _case) {
    int n = in.nextInt(), m = in.nextInt();
    ArrayList<ArrayList<LongOrderedPair>> adj = new ArrayList<>(n), adjT = new ArrayList<>(n);
    ArrayList<IntegerOrderedTriplet> edges = new ArrayList<>(m);
    for (int i = 0; i < n; i++) {
      adj.add(new ArrayList<>());
      adjT.add(new ArrayList<>());
    }

    for (int i = 0; i < m; i++) {
      int a = in.nextInt() - 1, b = in.nextInt() - 1, c = in.nextInt();
      adj.get(a).add(new LongOrderedPair(b, c));
      adjT.get(b).add(new LongOrderedPair(a, c));
      edges.add(new IntegerOrderedTriplet(a, b, c));
    }

    boolean[] processed = new boolean[n];
    long[] distance1 = new long[n];
    Arrays.fill(distance1, Long.MAX_VALUE >> 2);

    PriorityQueue<LongOrderedPair> queue1 = new PriorityQueue<>();
    distance1[0] = 0;
    queue1.add(new LongOrderedPair(0, 0));
    while (!queue1.isEmpty()) {
      var pair = queue1.poll();
      int a = (int) pair.second;
      if (processed[a]) {
        continue;
      }

      processed[a] = true;
      for (var u : adj.get(a)) {
        int b = (int) u.first, w = (int) u.second;
        if (distance1[a] + w < distance1[b]) {
          distance1[b] = distance1[a] + w;
          queue1.add(new LongOrderedPair(distance1[b], b));
        }
      }
    }

    Arrays.fill(processed, false);
    long[] distanceN = new long[n];
    Arrays.fill(distanceN, Long.MAX_VALUE >> 2);

    PriorityQueue<LongOrderedPair> queue2 = new PriorityQueue<>();
    distanceN[n - 1] = 0;
    queue2.add(new LongOrderedPair(0, n - 1));
    while (!queue2.isEmpty()) {
      var pair = queue2.poll();
      int a = (int) pair.second;
      if (processed[a]) {
        continue;
      }

      processed[a] = true;
      for (var u : adjT.get(a)) {
        int b = (int) u.first, w = (int) u.second;
        if (distanceN[a] + w < distanceN[b]) {
          distanceN[b] = distanceN[a] + w;
          queue2.add(new LongOrderedPair(distanceN[b], b));
        }
      }
    }

    long mn = Long.MAX_VALUE;
    for (var edge : edges) {
      int a = edge.first, b = edge.second, c = edge.third;
      long newDist = distance1[a] + (c >> 1) + distanceN[b];
      mn = Math.min(mn, newDist);
    }

    out.append(mn).appendNewLine();
  }

}

@MultipleInheritanceDisallowed(inheritor = FlightDiscount.class)
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

class IntegerOrderedTriplet
    implements Comparable<IntegerOrderedTriplet> {

  public int first;
  public int second;
  public int third;

  public IntegerOrderedTriplet(int first, int second, int third) {
    this.first = first;
    this.second = second;
    this.third = third;
  }

  @Override
  public int compareTo(IntegerOrderedTriplet other) {
    int cmp = Integer.compare(this.first, other.first);
    if (cmp != 0)
      return cmp;

    cmp = Integer.compare(this.second, other.second);
    if (cmp != 0)
      return cmp;

    return Integer.compare(this.third, other.third);
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof IntegerOrderedTriplet))
      return false;
    IntegerOrderedTriplet triplet = (IntegerOrderedTriplet) obj;
    return this.first == triplet.first && this.second == triplet.second
        && this.third == triplet.third;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.first, this.second, this.third);
  }
}

class LongOrderedPair implements Comparable<LongOrderedPair> {

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
