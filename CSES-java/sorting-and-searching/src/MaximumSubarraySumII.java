import java.util.Arrays;
import java.util.Comparator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

@Launchable(author = "Evermore", hostname = "probook", judge = "CSES")
public class MaximumSubarraySumII extends ModuleSignatures implements Runnable {

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
    new Thread(null, new MaximumSubarraySumII(), "LaunchableDriver", 1048576L).start();
  }

  private void solveCase(int _case) {
    int n = in.nextInt(), a = in.nextInt(), b = in.nextInt();
    long[] prefix = new long[n + 1];
    for (int i = 1; i <= n; i++) {
      int x = in.nextInt();
      prefix[i] = prefix[i - 1] + x;
    }

    TreeMultiset<Long> prefixStore = new TreeMultiset<>();
    long mx = Long.MIN_VALUE;
    for (int i = a; i <= n; i++) {
      prefixStore.add(prefix[i - a]);
      prefixStore.removeOne(i >= b + 1 ? prefix[i - b - 1] : Long.MIN_VALUE);
      mx = Math.max(mx, prefix[i] - prefixStore.first());
    }

    out.append(mx).appendNewLine();
  }

}

@MultipleInheritanceDisallowed(inheritor = MaximumSubarraySumII.class)
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

class TreeMultiset<E> {

  private TreeMap<E, Integer> map;
  private int size;

  public TreeMultiset() {
    this.map = new TreeMap<E, Integer>();
    this.size = 0;
  }

  public TreeMultiset(Comparator<? super E> comparator) {
    this.map = new TreeMap<E, Integer>(comparator);
    this.size = 0;
  }

  public boolean add(E e) {
    this.map.put(e, this.map.getOrDefault(e, 0) + 1);
    this.size += 1;
    return true;
  }

  public E ceiling(E e) {
    return this.map.ceilingKey(e);
  }

  public void clear() {
    this.map.clear();
    this.size = 0;
  }

  @Override
  public TreeMultiset<E> clone() {
    TreeMultiset<E> cloned = new TreeMultiset<>(this.map.comparator());
    cloned.map.putAll(this.map);
    cloned.size = this.size;
    return cloned;
  }

  public Comparator<? super E> comparator() {
    return this.map.comparator();
  }

  public boolean contains(Object o) {
    return this.map.containsKey(o);
  }

  public E first() {
    return this.map.firstKey();
  }

  public E floor(E e) {
    return this.map.floorKey(e);
  }

  public E higher(E e) {
    return this.map.higherKey(e);
  }

  public boolean isEmpty() {
    return this.size == 0;
  }

  public E last() {
    return this.map.lastKey();
  }

  public E lower(E e) {
    return this.map.lowerKey(e);
  }

  public int size() {
    return this.size;
  }

  public int count(E e) {
    return this.map.containsKey(e) ? this.map.get(e) : 0;
  }

  public Set<E> elementSet() {
    return this.map.keySet();
  }

  public Set<Map.Entry<E, Integer>> entryMultiset() {
    return this.map.entrySet();
  }

  public boolean removeOne(E e) {
    if (!this.map.containsKey(e))
      return false;

    Integer cnt = this.map.get(e);
    if (cnt == 1)
      this.map.remove(e);
    else
      this.map.put(e, --cnt);

    this.size -= 1;
    return true;
  }

  public boolean removeAll(E e) {
    if (!this.map.containsKey(e))
      return false;

    Integer cnt = this.map.get(e);
    this.map.remove(e);
    this.size -= cnt;
    return true;
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
