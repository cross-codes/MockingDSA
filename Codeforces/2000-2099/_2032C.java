import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;
import java.util.Map;
import java.util.NavigableMap;
import java.util.TreeMap;

public class _2032C {

  public static void main(String[] args) {
    final StandardInputReader in = new StandardInputReader();
    final StandardOutputWriter out = new StandardOutputWriter();

    int t = in.nextInt();
    while (t-- > 0) {
      final int n = in.nextInt();
      TreeMap<Integer, Integer> map = new TreeMap<>();
      ArrayList<Integer> uniqueElements = new ArrayList<>(map.keySet());
      for (int i = 0; i < n; i++) {
        int num = in.nextInt();
        map.put(num, map.getOrDefault(num, 0) + 1);
        uniqueElements.add(num);
      }

      uniqueElements.sort(Comparator.naturalOrder());

      int cnt = 0;
      while (true) {
        int currLength = map.size();
        if (currLength <= 2) {
          break;
        }
        int sumz = uniqueElements.get(currLength >> 1) +
            uniqueElements.get((currLength >> 1) - 1);
        if (sumz <= uniqueElements.get(currLength - 1)) {
          NavigableMap<Integer, Integer> badValues = map.tailMap(sumz - 1, false);
          Iterator<Map.Entry<Integer, Integer>> iterator = badValues.entrySet().iterator();
          while (iterator.hasNext()) {
            Map.Entry<Integer, Integer> entry = iterator.next();
            cnt += entry.getValue();
            uniqueElements.removeIf(num -> num.equals(entry.getKey()));
            iterator.remove();
          }
        } else if (uniqueElements.get(0) + uniqueElements.get(1) <= uniqueElements.get(currLength - 1)) {
          int val = uniqueElements.get(0);
          cnt += map.get(val);
          map.remove(val);
          uniqueElements.removeIf(num -> num.equals(val));
        } else
          break;
      }

      out.append(cnt).appendNewLine();
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