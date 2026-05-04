import java.util.Arrays;
import java.util.Iterator;
import java.util.function.IntConsumer;

@Launchable(author = "Evermore", hostname = "probook", judge = "CSES")
public class CommonDivisors extends ModuleSignatures implements Runnable {

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
    new Thread(null, new CommonDivisors(), "LaunchableDriver", 1048576L).start();
  }

  private void solveCase(int _case) {
    int n = in.nextInt();

    DensePrime primes = new DensePrime(1000001);
    int[] array = new int[1000001];
    for (int i = 0; i < n; i++) {
      int x = in.nextInt();
      primes.forFactors(x, true, true, factor -> array[factor]++);
    }

    for (int i = array.length - 1; i >= 0; i--) {
      if (array[i] > 1) {
        out.append(i).appendNewLine();
        return;
      }
    }
  }

}

@MultipleInheritanceDisallowed(inheritor = CommonDivisors.class)
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

@FunctionalInterface
interface IntBiConsumer {
  void accept(int t, int u);
}

class IntegerArrayList implements Cloneable, Iterable<Integer> {
  private static final int[] EMPTY = new int[0];
  private int[] array;
  private int size;

  public IntegerArrayList() {
    array = EMPTY;
  }

  public IntegerArrayList(int n) {
    array = new int[n];
  }

  public int size() {
    return size;
  }

  public IntegerArrayList clone() {
    try {
      IntegerArrayList clone = (IntegerArrayList) super.clone();
      clone.array = size == 0 ? EMPTY : array.clone();
      return clone;
    } catch (CloneNotSupportedException ex) {
      throw new RuntimeException();
    }
  }

  public Iterator<Integer> iterator() {
    return new IALIterator();
  }

  public void add(int e) {
    if (array.length == size) {
      if (array.length == 0)
        array = new int[4];
      else
        grow(size << 1);
    }
    array[size++] = e;
  }

  private void grow(int capacity) {
    int[] array = new int[capacity];
    System.arraycopy(this.array, 0, array, 0, size);
    this.array = array;
  }

  public int get(int index) {
    return array[index];
  }

  public void set(int index, int e) {
    array[index] = e;
  }

  public int remove() {
    return array[--size];
  }

  public void clear() {
    size = 0;
  }

  public int[] toArray() {
    int[] array = new int[size];
    System.arraycopy(this.array, 0, array, 0, size);
    return array;
  }

  public void sort() {
    Arrays.sort(array, 0, size);
  }

  private class IALIterator implements Iterator<Integer> {
    private int index;

    public boolean hasNext() {
      return index != size;
    }

    public Integer next() {
      return array[index++];
    }
  }
}

class DensePrime {
  private int[] minima, powers;
  private boolean[] parity, squareFree;

  public IntegerArrayList primes;

  public DensePrime(int N) {
    this.minima = new int[N];
    this.powers = new int[N];

    this.parity = new boolean[N];
    this.squareFree = new boolean[N];
    this.primes = new IntegerArrayList(N >> 1);

    for (int i = 2; i < (N + 1) >> 1; i++) {
      int minimum, power;
      if (this.minima[i] == 0) {
        minimum = i;
        power = 1;
        this.parity[i] = this.squareFree[i] = true;
        this.primes.add(i);
      } else {
        minimum = this.minima[i];
        power = this.powers[i];
      }

      for (int e : this.primes) {
        int index = e * i;
        if (index < N) {
          this.minima[index] = e;
          this.parity[index] = !this.parity[i];
          if (e == minimum) {
            this.powers[index] = power + 1;
            break;
          } else {
            this.powers[index] = 1;
            this.squareFree[index] = this.squareFree[i];
          }
        } else {
          break;
        }
      }
    }

    for (int i = (N + 1) >> 1 | 1; i < N; i += 2) {
      if (this.minima[i] == 0) {
        this.parity[i] = true;
        this.squareFree[i] = true;
      }
    }
  }

  boolean isSquareFree(int n) {
    return this.squareFree[n];
  }

  boolean getParity(int n) {
    return this.parity[n];
  }

  public int totient(int n) {
    int result = 1;
    while (minima[n] != 0) {
      int factor = 1;
      for (int i = 1; i < powers[n]; i++)
        factor *= minima[n];
      result *= factor * (minima[n] - 1);
      n /= factor * minima[n];
    }
    if (n != 1)
      result *= n - 1;
    return result;
  }

  public void forPrimeFactors(int n, IntConsumer consumer) {
    while (minima[n] != 0) {
      consumer.accept(minima[n]);
      int factor = 1;
      for (int i = 0; i < powers[n]; i++)
        factor *= minima[n];
      n /= factor;
    }
    if (n != 1)
      consumer.accept(n);
  }

  public void forPowers(int n, IntConsumer consumer) {
    while (minima[n] != 0) {
      consumer.accept(powers[n]);
      int factor = 1;
      for (int i = 0; i < powers[n]; i++)
        factor *= minima[n];
      n /= factor;
    }
    if (n != 1)
      consumer.accept(1);
  }

  public void forPrimeFactorsAndPowers(int n, IntBiConsumer biConsumer) {
    while (minima[n] != 0) {
      biConsumer.accept(minima[n], powers[n]);
      int factor = 1;
      for (int i = 0; i < powers[n]; i++)
        factor *= minima[n];
      n /= factor;
    }
    if (n != 1)
      biConsumer.accept(n, 1);
  }

  public void forFactors(int n, boolean includes1, boolean includesN, IntConsumer consumer) {
    if (n == 1) {
      if (includes1 && includesN)
        consumer.accept(1);
    } else {
      if (includes1)
        consumer.accept(1);
      IntegerArrayList primeFactors = new IntegerArrayList();
      IntegerArrayList powers = new IntegerArrayList();
      forPrimeFactorsAndPowers(n, (a, b) -> {
        primeFactors.add(a);
        powers.add(b);
      });
      int[] factors = primeFactors.toArray();
      int[] currentPowers = new int[factors.length];
      Arrays.fill(currentPowers, 1);
      int index = 0;
      while (true) {
        if (currentPowers[index] > powers.get(index))
          index++;
        else if (factors[index] == n) {
          if (includesN)
            consumer.accept(n);
          break;
        } else {
          consumer.accept(factors[index]);
          for (int i = 0; i <= index; i++)
            factors[i] = factors[index] * primeFactors.get(i);
          Arrays.fill(currentPowers, 0, index, 1);
          currentPowers[index]++;
          index = 0;
        }
      }
    }
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
