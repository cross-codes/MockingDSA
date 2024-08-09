import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.StringTokenizer;

public class Repetitions implements Runnable {

  StandardInputReader in;
  StandardOutputWriter out;
  StringTokenizer tok = new StringTokenizer("");

  public static void main(String[] args) {
    new Thread(null, new Repetitions(), "", 256 * (1L << 20)).start();
  }

  public void run() {
    try {
      in = new StandardInputReader(System.in);
      out = new StandardOutputWriter(System.out);
      solve();
      in.close();
      out.flush();
    } catch (Throwable t) {
      t.printStackTrace(System.err);
      System.exit(-1);
    }
  }

  String readString() throws IOException {
    while (!tok.hasMoreTokens()) {
      tok = new StringTokenizer(in.readLine());
    }
    return tok.nextToken();
  }

  int readInt() throws IOException {
    return Integer.parseInt(readString());
  }

  long readLong() throws IOException {
    return Long.parseLong(readString());
  }

  double readDouble() throws IOException {
    return Double.parseDouble(readString());
  }

  void solve() throws IOException {
    String seq = readString();
    int max = 1, l = 0, r = 0, n = seq.length();
    while (r < n) {
      char toCompare = seq.charAt(l);
      char currChar = seq.charAt(r);
      if (currChar != toCompare) {
        max = Math.max(max, r - l);
        l = r;
      } else r++;
    }

    out.println(Math.max(max, r - l));
  }

  static class StandardInputReader {
    private final int BUFFER_SIZE = 1 << 16;
    private DataInputStream din;
    private byte[] buffer;
    private int bufferPointer, bytesRead;

    public StandardInputReader(InputStream iStr) {
      din = new DataInputStream(iStr);
      buffer = new byte[BUFFER_SIZE];
      bufferPointer = bytesRead = 0;
    }

    public StandardInputReader(String file_name) throws IOException {
      din = new DataInputStream(new FileInputStream(file_name));
      buffer = new byte[BUFFER_SIZE];
      bufferPointer = bytesRead = 0;
    }

    public String readLine() throws IOException {
      byte[] buf = new byte[1024];
      int cnt = 0, c;
      while ((c = read()) != -1) {
        if (c == '\n') {
          if (cnt != 0) {
            break;
          } else {
            continue;
          }
        }
        if (cnt >= buf.length) {
          byte[] newBuf = new byte[buf.length * 2];
          System.arraycopy(buf, 0, newBuf, 0, buf.length);
          buf = newBuf;
        }
        buf[cnt++] = (byte) c;
      }
      return new String(buf, 0, cnt);
    }

    public int nextInt() throws IOException {
      int ret = 0;
      byte c = read();
      while (c <= ' ') {
        c = read();
      }
      boolean neg = (c == '-');
      if (neg) c = read();
      do {
        ret = ret * 10 + c - '0';
      } while ((c = read()) >= '0' && c <= '9');

      if (neg) return -ret;
      return ret;
    }

    public long nextLong() throws IOException {
      long ret = 0;
      byte c = read();
      while (c <= ' ') c = read();
      boolean neg = (c == '-');
      if (neg) c = read();
      do {
        ret = ret * 10 + c - '0';
      } while ((c = read()) >= '0' && c <= '9');
      if (neg) return -ret;
      return ret;
    }

    public double nextDouble() throws IOException {
      double ret = 0, div = 1;
      byte c = read();
      while (c <= ' ') c = read();
      boolean neg = (c == '-');
      if (neg) c = read();

      do {
        ret = ret * 10 + c - '0';
      } while ((c = read()) >= '0' && c <= '9');

      if (c == '.') {
        while ((c = read()) >= '0' && c <= '9') {
          ret += (c - '0') / (div *= 10);
        }
      }

      if (neg) return -ret;
      return ret;
    }

    private void fillBuffer() throws IOException {
      bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
      if (bytesRead == -1) buffer[0] = -1;
    }

    private byte read() throws IOException {
      if (bufferPointer == bytesRead) fillBuffer();
      return buffer[bufferPointer++];
    }

    public void close() throws IOException {
      if (din == null) return;
      din.close();
    }
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
        throw new RuntimeException("FastWriter");
      }
    }

    public StandardOutputWriter write(byte b) {
      buf[ptr++] = b;
      if (ptr == BUFFER_SIZE) innerflush();
      return this;
    }

    public StandardOutputWriter write(char c) {
      return write((byte) c);
    }

    public StandardOutputWriter write(char[] s) {
      for (char c : s) {
        buf[ptr++] = (byte) c;
        if (ptr == BUFFER_SIZE) innerflush();
      }
      return this;
    }

    public StandardOutputWriter write(String s) {
      s.chars()
          .forEach(
              c -> {
                buf[ptr++] = (byte) c;
                if (ptr == BUFFER_SIZE) innerflush();
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
      if (ptr + 12 >= BUFFER_SIZE) innerflush();
      if (x < 0) {
        write((byte) '-');
        x = -x;
      }
      int d = countDigits(x);
      for (int i = ptr + d - 1; i >= ptr; i--) {
        buf[i] = (byte) ('0' + x % 10);
        x /= 10;
      }
      ptr += d;
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
      if (ptr + 21 >= BUFFER_SIZE) innerflush();
      if (x < 0) {
        write((byte) '-');
        x = -x;
      }
      int d = countDigits(x);
      for (int i = ptr + d - 1; i >= ptr; i--) {
        buf[i] = (byte) ('0' + x % 10);
        x /= 10;
      }
      ptr += d;
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
        out.write(buf, 0, ptr);
        ptr = 0;
      } catch (IOException e) {
        throw new RuntimeException("innerflush");
      }
    }

    public void flush() {
      innerflush();
      try {
        out.flush();
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
