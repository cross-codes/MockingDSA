import java.util.Arrays;

@Launchable(author = "Evermore", hostname = "probook", judge = "CSES")
public class _2209B extends ModuleSignatures implements Runnable {

  private final StandardInputReader in = new StandardInputReader();
  private final StandardOutputWriter out = new StandardOutputWriter();
  @SuppressWarnings("unused")
  private final Debug dbg = Debug.getInstance();

  @Override
  public void run() {
    int t = in.nextInt();
    for (int _case = 1; _case <= t; _case++)
      this.solveCase(_case);
    this.out.flush();
  }

  public static void main(String... args) {
    new Thread(null, new _2209B(), "LaunchableDriver", 1048576L).start();
  }

  private void solveCase(int _case) {
    int n = in.nextInt();
    int[] a = in.readIntegerArray(n);

    IntegerIndexCompress ic = new IntegerIndexCompress(a.clone());
    int[] ac = Arrays.stream(a).map(ic::getCompressedIndex).toArray();

    WaveletMatrix wmm = new WaveletMatrix(ac, ic.getMaxRange());
    for (int i = 0; i < n; i++) {
      int v = ic.getCompressedIndex(a[i]);
      int ne = wmm.numEq(i + 1, n, v), nle = wmm.numLeq(i + 1, n, v);
      int nl = nle - ne, ng = n - i - 1 - nle;
      out.append(Math.max(nl, ng)).append(" ");
    }

    out.appendNewLine();
  }

}

@MultipleInheritanceDisallowed(inheritor = _2209B.class)
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

class IntegerIndexCompress {
  private final int[] arr;
  private final int size;

  public IntegerIndexCompress(int[] vec) {
    this.arr = vec;
    Arrays.sort(this.arr);

    int unique = 0;
    if (this.arr.length > 0) {
      unique = 1;
      for (int i = 1; i < this.arr.length; i++) {
        if (this.arr[i] != this.arr[i - 1]) {
          this.arr[unique++] = this.arr[i];
        }
      }
    }

    this.size = unique;
  }

  public int getCompressedIndex(int value) {
    int index = Arrays.binarySearch(this.arr, 0, this.size, value);
    return index >= 0 ? index : ~index;
  }

  public int getMaxRange() {
    return this.size - 1;
  }
}

class WaveletMatrix {
  private final int levels;
  private final int[][] pref;
  private final int[] zeroBoundary;

  public WaveletMatrix(int[] arr, int maxVal) {
    int n = arr.length;
    this.levels = 32 - Integer.numberOfLeadingZeros(Math.max(1, maxVal));

    this.pref = new int[levels][n + 1];
    this.zeroBoundary = new int[levels];

    int[] temp = new int[n];

    for (int l = levels - 1; l >= 0; l--) {
      int bit = 1 << l;
      int zeros = 0;

      for (int i = 0; i < n; i++) {
        if ((arr[i] & bit) == 0) {
          zeros++;
        }
        pref[l][i + 1] = zeros;
      }

      zeroBoundary[l] = zeros;

      int leftIdx = 0;
      int rightIdx = zeros;
      for (int i = 0; i < n; i++) {
        if ((arr[i] & bit) == 0) {
          temp[leftIdx++] = arr[i];
        } else {
          temp[rightIdx++] = arr[i];
        }
      }

      System.arraycopy(temp, 0, arr, 0, n);
    }
  }

  public int kthSmallestOneIndexed(int from, int exclTo, int k) {
    int ans = 0;
    for (int l = levels - 1; l >= 0; l--) {
      int zerosInLeft = pref[l][from];
      int zerosInRight = pref[l][exclTo];
      int zerosInInterval = zerosInRight - zerosInLeft;

      if (k <= zerosInInterval) {
        from = zerosInLeft;
        exclTo = zerosInRight;
      } else {
        from = zeroBoundary[l] + (from - zerosInLeft);
        exclTo = zeroBoundary[l] + (exclTo - zerosInRight);
        k -= zerosInInterval;
        ans |= (1 << l);
      }
    }

    return ans;
  }

  public int numEq(int from, int exclTo, int target) {
    if (target < 0 || target >= (1 << levels)) {
      return 0;
    }

    for (int l = levels - 1; l >= 0; l--) {
      int zerosInLeft = pref[l][from];
      int zerosInRight = pref[l][exclTo];

      if ((target & (1 << l)) == 0) {
        from = zerosInLeft;
        exclTo = zerosInRight;
      } else {
        from = zeroBoundary[l] + (from - zerosInLeft);
        exclTo = zeroBoundary[l] + (exclTo - zerosInRight);
      }

      if (from == exclTo) {
        return 0;
      }
    }

    return exclTo - from;
  }

  public int numLeq(int from, int exclTo, int target) {
    if (target < 0) {
      return 0;
    }
    if (target >= (1 << levels)) {
      return exclTo - from;
    }

    int count = 0;

    for (int l = levels - 1; l >= 0; l--) {
      int zerosInLeft = pref[l][from];
      int zerosInRight = pref[l][exclTo];
      int zerosInInterval = zerosInRight - zerosInLeft;

      if ((target & (1 << l)) == 0) {
        from = zerosInLeft;
        exclTo = zerosInRight;
      } else {
        count += zerosInInterval;
        from = zeroBoundary[l] + (from - zerosInLeft);
        exclTo = zeroBoundary[l] + (exclTo - zerosInRight);
      }

      if (from == exclTo) {
        return count;
      }
    }

    count += (exclTo - from);
    return count;
  }

  public int countInRange(int from, int exclTo, int minVal, int maxVal) {
    if (from >= exclTo || minVal > maxVal)
      return 0;

    int maxLimit = (1 << levels) - 1;
    if (maxVal > maxLimit)
      maxVal = maxLimit;
    if (minVal < 0)
      minVal = 0;
    if (minVal > maxVal)
      return 0;

    int targetMin = minVal - 1;
    boolean trackMin = targetMin >= 0;

    int countMax = 0, countMin = 0;
    int fMax = from, tMax = exclTo;
    int fMin = from, tMin = exclTo;

    for (int l = levels - 1; l >= 0; l--) {
      int[] p = pref[l];
      int zb = zeroBoundary[l];
      int bit = 1 << l;

      int zlMax = p[fMax];
      int zrMax = p[tMax];
      if ((maxVal & bit) == 0) {
        fMax = zlMax;
        tMax = zrMax;
      } else {
        countMax += (zrMax - zlMax);
        fMax = zb + fMax - zlMax;
        tMax = zb + tMax - zrMax;
      }

      if (trackMin) {
        int zlMin = p[fMin];
        int zrMin = p[tMin];
        if ((targetMin & bit) == 0) {
          fMin = zlMin;
          tMin = zrMin;
        } else {
          countMin += (zrMin - zlMin);
          fMin = zb + fMin - zlMin;
          tMin = zb + tMin - zrMin;
        }
      }
    }

    countMax += (tMax - fMax);
    if (trackMin) {
      countMin += (tMin - fMin);
    }

    return countMax - countMin;
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
