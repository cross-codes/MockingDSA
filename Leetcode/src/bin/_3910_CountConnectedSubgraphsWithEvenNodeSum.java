import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;

class Solution {
  public int evenSumSubgraphs(int[] nums, int[][] edges) {
    int n = nums.length;

    IntVector[] adj = new IntVector[n];
    for (int i = 0; i < n; i++) {
      adj[i] = new IntVector();
    }

    for (var edge : edges) {
      int u = edge[0], v = edge[1];
      adj[u].add(v);
      adj[v].add(u);
    }

    int cnt = 0;
    for (int i = 1; i < (1 << n); i++) {
      HashSet<Integer> vertices = new HashSet<>();
      for (int j = 0; j < 31; j++) {
        if ((i & (1 << j)) != 0) {
          vertices.add(j);
        }
      }

      boolean[] visited = new boolean[n];
      int[] nodeSum = new int[1];
      DFS dfs = (instance, u) -> {
        visited[u] = true;
        nodeSum[0] += nums[u];
        for (int e : adj[u]) {
          if (vertices.contains(e) && !visited[e]) {
            instance.run(instance, e);
          }
        }
      };

      dfs.run(dfs, Integer.numberOfTrailingZeros(i));

      boolean ok = true;
      for (int j = 0; j < n; j++) {
        if (!visited[j] && vertices.contains(j)) {
          ok = false;
        }
      }

      if (!ok) {
        continue;
      }

      if (((nodeSum[0] & 1) == 0)) {
        cnt += 1;
      }
    }

    return cnt;
  }
}

interface DFS {
  void run(DFS instance, int i);
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
