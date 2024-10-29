import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;

public class _402E {

  public static void main(String[] args) {
    final StandardInputReader in = new StandardInputReader();
    final StandardOutputWriter out = new StandardOutputWriter();

    int n = in.nextInt();
    int[][] a = new int[n][];
    for (int i = 0; i < n; i++)
      a[i] = in.readIntegerArray(n);

    SCC scc = new SCC(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (a[i][j] > 0 && i != j) {
          scc.add(i, j);
        }
      }
    }
    scc.go();

    out.append(scc.cs == 1 ? "YES" : "NO");
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

class SCC {
  public ArrayList<Integer>[] adj;
  public ArrayList<Integer>[] comp;
  public int n;
  public int idx, cs;
  public boolean[] u;
  public int[] pre, low, map;
  public ArrayDeque<Integer> s;

  public SCC(int nn) {
    adj = new ArrayList[n = nn];
    for (int curr = 0; curr < n; ++curr)
      adj[curr] = new ArrayList<>();
  }

  public void add(int v1, int v2) {
    adj[v1].add(v2);
  }

  public int[] go() {
    comp = new ArrayList[n];
    idx = 1;
    cs = 0;
    pre = new int[n];
    low = new int[n];
    map = new int[n];
    u = new boolean[n];
    s = new ArrayDeque<Integer>();
    for (int i = 0; i < n; ++i)
      if (pre[i] == 0)
        dfs(i);
    return map;
  }

  public void dfs(int v) {
    pre[v] = low[v] = idx++;
    s.push(v);
    u[v] = true;
    for (int to : adj[v]) {
      if (pre[to] == 0) {
        dfs(to);
        low[v] = Math.min(low[v], low[to]);
      } else if (u[to]) {
        low[v] = Math.min(low[v], pre[to]);
      }
    }
    if (low[v] == pre[v]) {
      int next;
      comp[cs] = new ArrayList<>();
      do {
        next = s.pop();
        u[next] = false;
        map[next] = cs;
        comp[cs].add(next);
      } while (next != v);
      cs++;
    }
  }

  public ArrayList<Integer>[] compressSCC() {
    ArrayList<Integer>[] g = new ArrayList[cs];
    for (int i = 0; i < cs; i++)
      g[i] = new ArrayList<Integer>();
    int[] added = new int[cs];
    Arrays.fill(added, -1);
    for (int i = 0; i < cs; i++) {
      for (int v : comp[i]) {
        for (int to : adj[v]) {
          int mapTo = map[to];
          if (mapTo != i && added[mapTo] != i) {
            g[i].add(mapTo);
            added[mapTo] = i;
          }
        }
      }
    }
    return g;
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
