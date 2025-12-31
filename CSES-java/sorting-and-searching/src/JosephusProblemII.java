import java.util.Arrays;

@Launchable(author = "Evermore", hostname = "probook", judge = "CSES")
public class JosephusProblemII extends ModuleSignatures implements Runnable {

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
    new Thread(null, new JosephusProblemII(), "LaunchableDriver", 1048576L).start();
  }

  private void solveCase(int _case) {
    int n = in.nextInt(), k = in.nextInt();
    IntegerBinarySearchTree bst = new IntegerBinarySearchTree(n + 1);
    for (int i = 1; i <= n; i++) {
      bst.set(i);
    }

    bst.build();
    int currPos = 0;
    while (bst.size() != 0) {
      n = bst.size();
      int nextPos = (currPos + k) % n;
      int val = bst.findByOrder(nextPos);

      out.append(val).append(" ");
      bst.removeOne(val);
      currPos = nextPos;
    }

    out.appendNewLine();
  }

}

@MultipleInheritanceDisallowed(inheritor = JosephusProblemII.class)
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

final class IntegerBinarySearchTree {
  private Node root;
  private final Node[] leaves;

  public IntegerBinarySearchTree(int n) {
    leaves = new Node[Integer.highestOneBit(n) << 1];
    for (int i = 0; i < leaves.length; i++)
      leaves[i] = new Node(null, null, 0);
  }

  public void set(int element) {
    leaves[element].value = 1;
  }

  public void build() {
    Node[] nodes = leaves;
    while (nodes.length != 1) {
      Node[] newNodes = new Node[nodes.length / 2];
      for (int i = 0; i < newNodes.length; i++) {
        Node left = nodes[i * 2];
        Node right = nodes[i * 2 + 1];
        newNodes[i] = new Node(left, right, left.value + right.value);
        left.parent = right.parent = newNodes[i];
      }
      nodes = newNodes;
    }
    root = nodes[0];
  }

  public int size() {
    return root.value;
  }

  public boolean contains(int element) {
    return leaves[element].value != 0;
  }

  public int orderOfKey(int x) {
    int index = 0;
    for (Node node = leaves[x]; node != root; node = node.parent) {
      if (node.parent.right == node)
        index += node.parent.left.value;
    }
    return leaves[x].value == 0 ? -index - 1 : index;
  }

  public void add(int element) {
    for (Node node = leaves[element]; node != null; node = node.parent)
      node.value++;
  }

  public void removeOne(int element) {
    for (Node node = leaves[element]; node != null; node = node.parent)
      node.value--;
  }

  public int findByOrder(int k) {
    int element = 0;
    int step = leaves.length / 2;
    for (Node node = root; node.left != null; step >>= 1) {
      if (k < node.left.value)
        node = node.left;
      else {
        k -= node.left.value;
        element += step;
        node = node.right;
      }
    }
    return element;
  }

  private static class Node {
    private Node parent;
    private final Node left;
    private final Node right;
    private int value;

    private Node(Node left, Node right, int value) {
      this.left = left;
      this.right = right;
      this.value = value;
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
