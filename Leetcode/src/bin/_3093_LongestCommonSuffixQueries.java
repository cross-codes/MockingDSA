import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

class Solution {
  public int[] stringIndices(String[] wordsContainer, String[] wordsQuery) {
    int n = wordsContainer.length, q = wordsQuery.length;
    for (int i = 0; i < n; i++) {
      wordsContainer[i] = new StringBuilder(wordsContainer[i]).reverse().toString();
    }

    for (int i = 0; i < q; i++) {
      wordsQuery[i] = new StringBuilder(wordsQuery[i]).reverse().toString();
    }

    long A = (StaticRandom.nextInt() >>> 1) | 1;
    int B = 1_000_000_000 + StaticRandom.nextInt(1_000_000_000) | 1;

    StringHash[] wordsContainerHashed = new StringHash[n];
    for (int i = 0; i < n; i++)
      wordsContainerHashed[i] = new StringHash(wordsContainer[i], A, B);

    int gbidx = 0;
    for (int i = 1; i < n; i++) {
      if (wordsContainer[i].length() < wordsContainer[gbidx].length()) {
        gbidx = i;
      }
    }

    Map<Long, Integer> hashToIdx = new HashMap<>();
    for (int i = 0; i < n; i++) {
      StringHash h = wordsContainerHashed[i];
      for (int len = 0; len <= h.m; len++) {
        long hash = h.getBidirectionalHash(0, len);
        if (!hashToIdx.containsKey(hash)) {
          hashToIdx.put(hash, i);
        } else {
          if (wordsContainer[i].length() < wordsContainer[hashToIdx.get(hash)].length()) {
            hashToIdx.put(hash, i);
          }
        }
      }
    }

    BinarySearchRoutine GLCP = (StringHash h1) -> {
      int L = 0, R = h1.m + 1;
      while (R - L > 1) {
        int M = L + ((R - L) >>> 1);
        if (!hashToIdx.containsKey(h1.getBidirectionalHash(0, M)))
          R = M;
        else
          L = M;
      }

      return L;
    };

    int[] res = new int[q];
    for (int i = 0; i < q; i++) {
      var hash = new StringHash(wordsQuery[i], A, B);
      int idx = GLCP.get(hash);
      if (idx == 0)
        res[i] = gbidx;
      else
        res[i] = hashToIdx.get(hash.getBidirectionalHash(0, idx));
    }

    return res;
  }
}

@FunctionalInterface
interface BinarySearchRoutine {
  int get(StringHash h1);
}

final class StaticRandom {
  private static long seed = System.nanoTime() ^ 8682522807148012L;

  private StaticRandom() {
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

  @Override
  protected Object clone() throws CloneNotSupportedException {
    throw new CloneNotSupportedException();
  }
}

class IntVector implements Cloneable, Iterable<Integer> {
  private static final int[] EMPTY = new int[0];
  private int[] array;
  private int size;

  public IntVector() {
    array = EMPTY;
  }

  public IntVector(int n) {
    array = new int[n];
  }

  public int size() {
    return size;
  }

  public IntVector clone() {
    try {
      IntVector clone = (IntVector) super.clone();
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
        ensureCapacity(size << 1);
    }
    array[size++] = e;
  }

  public void ensureCapacity(int capacity) {
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

class StringHash {
  public IntVector powers, prefixHashes, suffixHashes;
  public long A;
  public int B;
  public int m;

  public StringHash(String s, long A, int B) {
    this.m = s.length();

    this.powers = new IntVector(this.m + 1);
    this.prefixHashes = new IntVector(this.m + 1);
    this.suffixHashes = new IntVector(this.m + 1);

    for (int i = 0; i <= this.m; i++) {
      this.powers.add(1);
      this.prefixHashes.add(1);
      this.suffixHashes.add(1);
    }

    this.A = A;
    this.B = B;

    for (int i = 1; i <= this.m; i++) {
      long p = (this.powers.get(i - 1) * this.A) % this.B;
      this.powers.set(i, (int) ((p + this.B) % this.B));

      long ph = (this.prefixHashes.get(i - 1) * this.A + s.charAt(i - 1)) % this.B;
      this.prefixHashes.set(i, (int) ((ph + this.B) % this.B));

      long sh = (this.suffixHashes.get(i - 1) * this.A + s.charAt(this.m - i)) % this.B;
      this.suffixHashes.set(i, (int) ((sh + this.B) % this.B));
    }
  }

  public int getHash(int l, int r) {
    long h = (long) this.prefixHashes.get(r) - (long) this.prefixHashes.get(l) * this.powers.get(r - l);
    return (int) ((h % this.B + this.B) % this.B);
  }

  public int getReverseHash(int l, int r) {
    int revL = this.m - r;
    int revR = this.m - l;
    long h = (long) this.suffixHashes.get(revR) - (long) this.suffixHashes.get(revL) * this.powers.get(revR - revL);
    return (int) ((h % this.B + this.B) % this.B);
  }

  public long getBidirectionalHash(int l, int r) {
    long forward = getHash(l, r);
    long backward = getReverseHash(l, r);
    return (forward << 32) | (backward & 0xFFFFFFFFL);
  }
}
