package graphs;

public class DisjointSetForest {
  public int[] sizes, parents;

  public DisjointSetForest(int n) {
    this.sizes = new int[n];
    this.parents = new int[n];

    for (int i = 0; i < n; i++) {
      makeSet(i);
    }
  }

  private void makeSet(int u) {
    parents[u] = u;
    sizes[u] = 1;
  }

  public int findSet(int u) {
    if (parents[u] == u) {
      return u;
    }
    else {
      return parents[u] = findSet(parents[u]);
    }
  }

  boolean unite(int x, int y) {
    int xRoot = findSet(x), yRoot = findSet(y);

    if (xRoot == yRoot) {
      return false;
    }

    if (sizes[xRoot] < sizes[yRoot]) {
      int temp = xRoot;
      xRoot = yRoot;
      yRoot = temp;
    }

    sizes[xRoot] += sizes[yRoot];
    parents[yRoot] = xRoot;

    return true;
  }
}
