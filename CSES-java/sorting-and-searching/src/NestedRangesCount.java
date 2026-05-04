import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Objects;
import java.util.function.Consumer;

@Launchable(author = "Evermore", hostname = "probook", judge = "CSES")
public class NestedRangesCount extends ModuleSignatures implements Runnable {

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
    new Thread(null, new NestedRangesCount(), "LaunchableDriver", 1048576L).start();
  }

  private void solveCase(int _case) {
    int n = in.nextInt();
    int[] firstPass = new int[n], secondPass = new int[n];
    var ref = new IntegerOrderedPair(-1, -1);

    ArrayList<IntegerOrderedTriplet> intervals = new ArrayList<>(n);
    for (int i = 0; i < n; i++) {
      intervals.add(new IntegerOrderedTriplet(in.nextInt(), in.nextInt(), i));
    }

    intervals
        .sort((a, b) -> (a.first == b.first) ? Integer.compare(a.second, b.second) : Integer.compare(b.first, a.first));

    AVLTreeSet<IntegerOrderedPair> rightEndPoints = new AVLTreeSet<>();
    int gcnt = 0;

    for (var item : intervals) {
      ref.first = item.second;
      ref.second = Integer.MAX_VALUE;

      firstPass[item.third] = rightEndPoints.countLower(ref);
      rightEndPoints.add(new IntegerOrderedPair(item.second, gcnt++));
    }

    intervals
        .sort((a, b) -> (a.first == b.first) ? Integer.compare(b.second, a.second) : Integer.compare(a.first, b.first));

    rightEndPoints = new AVLTreeSet<>();
    gcnt = 0;

    for (var item : intervals) {
      ref.first = item.second;
      ref.second = Integer.MIN_VALUE;
      secondPass[item.third] = rightEndPoints.countHigher(ref);
      rightEndPoints.add(new IntegerOrderedPair(item.second, gcnt++));
    }

    for (int e : firstPass) {
      out.append(e).append(" ");
    }

    out.appendNewLine();

    for (int e : secondPass) {
      out.append(e).append(" ");
    }

    out.appendNewLine();
  }
}

@MultipleInheritanceDisallowed(inheritor = NestedRangesCount.class)
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

class IntegerOrderedPair implements Comparable<IntegerOrderedPair> {

  public int first;
  public int second;

  public IntegerOrderedPair(int first, int second) {
    this.first = first;
    this.second = second;
  }

  @Override
  public int compareTo(IntegerOrderedPair other) {
    int cmp = Integer.compare(this.first, other.first);
    if (cmp == 0)
      return Integer.compare(this.second, other.second);

    return cmp;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof IntegerOrderedPair))
      return false;
    IntegerOrderedPair pair = (IntegerOrderedPair) obj;
    return this.first == pair.first && this.second == pair.second;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.first, this.second);
  }
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

class AVLTreeSet<E> {
  private Item<E> root;
  private final Comparator<? super E> comparator;

  @SuppressWarnings("unchecked")
  public AVLTreeSet() {
    this.comparator = (Comparator<? super E>) Comparator.naturalOrder();
  }

  public AVLTreeSet(Comparator<? super E> cmp) {
    this.comparator = cmp;
  }

  public int size() {
    return root == null ? 0 : root.size;
  }

  public void forEach(Consumer<E> consumer) {
    forEach(root, consumer);
  }

  private void forEach(Item<E> item, Consumer<E> consumer) {
    if (item != null) {
      forEach(item.left, consumer);
      consumer.accept(item.element);
      forEach(item.right, consumer);
    }
  }

  public E findByOrder(int k) {
    Item<E> item = root;
    while (true) {
      int leftSize = (item.left != null) ? item.left.size : 0;

      if (k < leftSize) {
        item = item.left;
      } else if (k > leftSize) {
        k -= (leftSize + 1);
        item = item.right;
      } else {
        return item.element;
      }
    }
  }

  public E lowerBound(E e) {
    Item<E> item = root;
    E result = null;

    while (item != null) {
      int comparison = comparator.compare(e, item.element);
      if (comparison <= 0) {
        result = item.element;
        item = item.left;
      } else {
        item = item.right;
      }
    }
    return result;
  }

  public E upperBound(E e) {
    Item<E> item = root;
    E result = null;

    while (item != null) {
      int comparison = comparator.compare(e, item.element);
      if (comparison < 0) {
        result = item.element;
        item = item.left;
      } else {
        item = item.right;
      }
    }
    return result;
  }

  public boolean add(E e) {
    if (root == null)
      root = new Item<>(e, null);
    else {
      Item<E> item = root;
      Item<E> child;
      while (true) {
        int comparison = comparator.compare(e, item.element);
        if (comparison < 0) {
          if (item.left == null) {
            item.left = new Item<>(e, item);
            child = item.left;
            break;
          } else
            item = item.left;
        } else if (comparison > 0) {
          if (item.right == null) {
            item.right = new Item<>(e, item);
            child = item.right;
            break;
          } else
            item = item.right;
        } else
          return false;
      }
      while (true) {
        if (item == null)
          return true;
        item.size++;
        if (item.left == child) {
          if (item.balanceFactor == 1) {
            if (child.balanceFactor == 1)
              rotateLL(item, child);
            else
              rotateLR(item, child, child.right);
            item = item.parent;
            break;
          } else if (++item.balanceFactor == 0)
            break;
        } else {
          if (item.balanceFactor == -1) {
            if (child.balanceFactor == -1)
              rotateRR(item, child);
            else
              rotateRL(item, child, child.left);
            item = item.parent;
            break;
          } else if (--item.balanceFactor == 0)
            break;
        }
        child = item;
        item = item.parent;
      }
      for (item = item.parent; item != null; item = item.parent)
        item.size++;
    }
    return true;
  }

  public void remove(E e) {
    for (Item<E> item = root; item != null;) {
      int comparison = comparator.compare(e, item.element);
      if (comparison < 0)
        item = item.left;
      else if (comparison > 0)
        item = item.right;
      else {
        remove(item);
        break;
      }
    }
  }

  public int countHigher(E e) {
    int count = 0;
    for (Item<E> item = root; item != null;) {
      int comparison = comparator.compare(e, item.element);
      if (comparison < 0) {
        count += item.right == null ? 1 : item.right.size + 1;
        item = item.left;
      } else if (comparison > 0)
        item = item.right;
      else {
        if (item.right != null)
          count += item.right.size;
        break;
      }
    }
    return count;
  }

  public int countLower(E e) {
    int count = 0;
    for (Item<E> item = root; item != null;) {
      int comparison = comparator.compare(e, item.element);
      if (comparison > 0) {
        count += item.left == null ? 1 : item.left.size + 1;
        item = item.right;
      } else if (comparison < 0)
        item = item.left;
      else {
        if (item.left != null)
          count += item.left.size;
        break;
      }
    }
    return count;
  }

  private void remove(Item<E> item) {
    if (item.left != null && item.right != null) {
      Item<E> next = item.right;
      while (next.left != null)
        next = next.left;
      item.element = next.element;
      item = next;
    } else if (item == root) {
      if (root.size == 1)
        root = null;
      else {
        root = item.left == null ? item.right : item.left;
        root.parent = null;
      }
      return;
    }
    Item<E> removed = item;
    while (true) {
      Item<E> child = item;
      item = item.parent;
      if (item == null) {
        child = removed.left == null ? removed.right : removed.left;
        if (removed.parent.left == removed)
          removed.parent.left = child;
        else
          removed.parent.right = child;
        if (child != null)
          child.parent = removed.parent;
        return;
      }
      item.size--;
      if (item.left == child) {
        if (item.balanceFactor == -1) {
          child = item.right;
          if (child.balanceFactor == 0) {
            rotateRO(item, child);
            item = child;
            break;
          } else {
            if (child.balanceFactor == -1)
              rotateRR(item, child);
            else
              rotateRL(item, child, child.left);
            item = item.parent;
          }
        } else if (item.balanceFactor-- == 0)
          break;
      } else {
        if (item.balanceFactor == 1) {
          child = item.left;
          if (child.balanceFactor == 0) {
            rotateLO(item, child);
            item = child;
            break;
          } else {
            if (child.balanceFactor == 1)
              rotateLL(item, child);
            else
              rotateLR(item, child, child.right);
            item = item.parent;
          }
        } else if (item.balanceFactor++ == 0)
          break;
      }
    }
    for (item = item.parent; item != null; item = item.parent)
      item.size--;
    Item<E> child = removed.left == null ? removed.right : removed.left;
    if (removed.parent.left == removed)
      removed.parent.left = child;
    else
      removed.parent.right = child;
    if (child != null)
      child.parent = removed.parent;
  }

  private void rotateLL(Item<E> item, Item<E> child) {
    item.balanceFactor = 0;
    child.balanceFactor = 0;
    replaceAsChild(item, child);
    if (child.right == null) {
      child.size = 3;
      item.size = 1;
      item.left = null;
    } else {
      child.size = item.size;
      item.size -= child.left.size + 1;
      setLeft(item, child.right);
    }
    setRight(child, item);
  }

  private void rotateLO(Item<E> item, Item<E> child) {
    item.balanceFactor = 1;
    child.balanceFactor = -1;
    replaceAsChild(item, child);
    child.size = item.size;
    item.size -= child.left.size + 1;
    setLeft(item, child.right);
    setRight(child, item);
  }

  private void rotateLR(Item<E> item, Item<E> child, Item<E> grandchild) {
    replaceAsChild(item, grandchild);
    if (grandchild.balanceFactor == -1) {
      item.balanceFactor = 0;
      child.balanceFactor = 1;
      grandchild.balanceFactor = 0;
      if (grandchild.left == null) {
        grandchild.size = 6;
        item.size = 3;
        child.size = 2;
        setLeft(item, grandchild.right);
        child.right = null;
        setRight(grandchild, item);
        setLeft(grandchild, child);
        return;
      }
    } else if (grandchild.balanceFactor == 0) {
      item.balanceFactor = 0;
      child.balanceFactor = 0;
      if (child.left == null) {
        grandchild.size = 3;
        item.size = 1;
        child.size = 1;
        item.left = null;
        child.right = null;
        setRight(grandchild, item);
        setLeft(grandchild, child);
        return;
      }
    } else {
      item.balanceFactor = -1;
      child.balanceFactor = 0;
      grandchild.balanceFactor = 0;
      if (grandchild.right == null) {
        grandchild.size = 6;
        item.size = 2;
        child.size = 3;
        item.left = null;
        setRight(child, grandchild.left);
        setRight(grandchild, item);
        setLeft(grandchild, child);
        return;
      }
    }
    grandchild.size = item.size;
    item.size -= child.size - grandchild.right.size;
    child.size -= grandchild.right.size + 1;
    setLeft(item, grandchild.right);
    setRight(child, grandchild.left);
    setRight(grandchild, item);
    setLeft(grandchild, child);
  }

  private void rotateRR(Item<E> item, Item<E> child) {
    item.balanceFactor = 0;
    child.balanceFactor = 0;
    replaceAsChild(item, child);
    if (child.left == null) {
      child.size = 3;
      item.size = 1;
      item.right = null;
    } else {
      child.size = item.size;
      item.size -= child.right.size + 1;
      setRight(item, child.left);
    }
    setLeft(child, item);
  }

  private void rotateRO(Item<E> item, Item<E> child) {
    item.balanceFactor = -1;
    child.balanceFactor = 1;
    replaceAsChild(item, child);
    child.size = item.size;
    item.size -= child.right.size + 1;
    setRight(item, child.left);
    setLeft(child, item);
  }

  private void rotateRL(Item<E> item, Item<E> child, Item<E> grandchild) {
    replaceAsChild(item, grandchild);
    if (grandchild.balanceFactor == 1) {
      item.balanceFactor = 0;
      child.balanceFactor = -1;
      grandchild.balanceFactor = 0;
      if (grandchild.right == null) {
        grandchild.size = 6;
        item.size = 3;
        child.size = 2;
        setRight(item, grandchild.left);
        child.left = null;
        setLeft(grandchild, item);
        setRight(grandchild, child);
        return;
      }
    } else if (grandchild.balanceFactor == 0) {
      item.balanceFactor = 0;
      child.balanceFactor = 0;
      if (child.right == null) {
        grandchild.size = 3;
        item.size = 1;
        child.size = 1;
        item.right = null;
        child.left = null;
        setLeft(grandchild, item);
        setRight(grandchild, child);
        return;
      }
    } else {
      item.balanceFactor = 1;
      child.balanceFactor = 0;
      grandchild.balanceFactor = 0;
      if (grandchild.left == null) {
        grandchild.size = 6;
        item.size = 2;
        child.size = 3;
        item.right = null;
        setLeft(child, grandchild.right);
        setLeft(grandchild, item);
        setRight(grandchild, child);
        return;
      }
    }
    grandchild.size = item.size;
    item.size -= child.size - grandchild.left.size;
    child.size -= grandchild.left.size + 1;
    setRight(item, grandchild.left);
    setLeft(child, grandchild.right);
    setLeft(grandchild, item);
    setRight(grandchild, child);
  }

  private void replaceAsChild(Item<E> oldItem, Item<E> newItem) {
    Item<E> parent = oldItem.parent;
    if (parent == null)
      root = newItem;
    else if (parent.left == oldItem)
      parent.left = newItem;
    else
      parent.right = newItem;
    newItem.parent = parent;
  }

  private void setLeft(Item<E> item, Item<E> child) {
    item.left = child;
    child.parent = item;
  }

  private void setRight(Item<E> item, Item<E> child) {
    item.right = child;
    child.parent = item;
  }

  private static class Item<E> {
    private E element;
    private Item<E> parent;
    private Item<E> left;
    private Item<E> right;
    private int balanceFactor;
    private int size = 1;

    private Item(E element, Item<E> parent) {
      this.element = element;
      this.parent = parent;
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
