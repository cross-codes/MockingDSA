import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Comparator;
import java.util.Map;
import java.util.TreeMap;
import java.util.TreeSet;

public class _1691B {

  private static InputReader in;
  private static OutputWriter out;

  public static void main(String[] args) {
    new Thread(null, IO_PROC, "", 256 * (1L << 20)).start();
  }

  private static final Runnable IO_PROC = () -> {
    try {
      in = new InputReader(System.in);
      out = new OutputWriter(System.out);
      solve();
      out.flush();
    } catch (Throwable t) {
      t.printStackTrace(System.err);
      System.exit(-1);
    }
  };

  private static void solve() throws IOException {
    int t = in.nextInt();
    iter: while (t-- > 0) {
      final StringBuilder sb = new StringBuilder();
      int n = in.nextInt();

      int[] sizes = new int[n];
      MultiValueRBMap map = new MultiValueRBMap();
      for (int i = 1; i <= n; i++) {
        int size = in.nextInt();
        sizes[i - 1] = size;
        map.addValueToKeyOrDefault(size, i);
      }

      for (int i = 1; i <= n; i++) {
        Map.Entry<Integer, TreeSet<Integer>> entry = map.ceilingEntry(sizes[i - 1]);

        if (entry == null) {
          out.append(-1).appendNewLine();
          continue iter;
        }
        TreeSet<Integer> people = entry.getValue();

        if (people.size() > 1 || (people.size() > 0 && !people.contains(i))) {
          boolean toAddBack = false;

          if (people.contains(i)) {
            people.remove(i);
            toAddBack = true;
          }

          Integer value = people.last();
          people.remove(value);

          if (toAddBack)
            people.add(i);

          sb.append(value).append(" ");
        } else {
          Integer key = map.higherKey(sizes[i - 1]);

          if (key == null) {
            out.append(-1).appendNewLine();
            continue iter;
          }
          people = map.get(key);

          Integer value = people.last();
          map.removeValueFromKey(key, value);

          sb.append(value).append(" ");
        }
      }

      out.append(sb.toString()).appendNewLine();
    }
  }

  @FunctionalInterface
  private static interface Procedure {
    void run();
  }

  @FunctionalInterface
  private static interface LongFunction {
    long apply(long t);
  }

  @SuppressWarnings("unused")
  private static class MultiValueRBMap extends TreeMap<Integer, TreeSet<Integer>> {
    public MultiValueRBMap() {
      super();
    }

    public MultiValueRBMap(Comparator<? super Integer> comp) {
      super(comp);
    }

    public boolean removeValueFromKey(Integer key, Integer value) {
      if (key == null)
        return false;

      TreeSet<Integer> values = this.get(key);
      if (values != null && values.remove(value)) {
        if (values.isEmpty())
          this.remove(key);
        return true;
      }

      return false;
    }

    public boolean addValueToKeyOrDefault(Integer key, Integer value) {
      if (key == null)
        return false;

      this.computeIfAbsent(key, k -> new TreeSet<>()).add(value);
      return true;
    }
  }

  @SuppressWarnings("unused")
  private static class InputReader {

    private final byte[] buffer;
    private int pos;
    private final InputStream in;

    public InputReader(InputStream is) {
      this.in = is;
      try {
        this.buffer = new byte[this.in.available() + 1];
        this.buffer[this.buffer.length - 1] = '\n';
        this.in.read(this.buffer);
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

  @SuppressWarnings("unused")
  private static class OutputWriter {

    private static final int BUFFER_SIZE = 1048576;
    private final byte[] buffer;
    private final OutputStream out;
    private int pos;

    public OutputWriter(OutputStream os) {
      this.out = os;
      this.buffer = new byte[BUFFER_SIZE];
    }

    public OutputWriter append(String s) throws IOException {
      int length = s.length();
      this.ensureCapacity(length);
      for (int i = 0; i < length; i++)
        this.buffer[this.pos++] = (byte) s.charAt(i);
      return this;
    }

    public OutputWriter append(byte[] bytes) throws IOException {
      if (BUFFER_SIZE - this.pos < bytes.length) {
        this.flush();
        if (bytes.length > BUFFER_SIZE) {
          this.out.write(bytes, 0, bytes.length);
          return this;
        }
      }
      for (byte b : bytes)
        this.buffer[this.pos++] = b;
      return this;
    }

    public OutputWriter append(byte[] bytes, int from, int to) throws IOException {
      int length = to - from;
      if (BUFFER_SIZE - this.pos < length) {
        this.flush();
        if (length > BUFFER_SIZE) {
          this.out.write(bytes, from, length);
          return this;
        }
      }
      for (int i = from; i < to; i++)
        this.buffer[this.pos++] = bytes[i];
      return this;
    }

    public OutputWriter append(char c) throws IOException {
      this.ensureCapacity(1);
      this.buffer[this.pos++] = (byte) c;
      return this;
    }

    public OutputWriter append(int i) throws IOException {
      return this.append(Integer.toString(i));
    }

    public OutputWriter append(long l) throws IOException {
      return this.append(Long.toString(l));
    }

    public OutputWriter append(double d) throws IOException {
      return this.append(Double.toString(d));
    }

    public void appendNewLine() throws IOException {
      this.ensureCapacity(1);
      this.buffer[this.pos++] = '\n';
    }

    public void flush() throws IOException {
      this.out.write(this.buffer, 0, this.pos);
      this.pos = 0;
    }

    private void ensureCapacity(int n) throws IOException {
      if (BUFFER_SIZE - this.pos < n)
        this.flush();
    }
  }
}