#include <vector>

struct DisjointSetForest {
 public:
  std::vector<int> sizes, parents;

  DisjointSetForest(int n) : sizes(n), parents(n) {
    for (int u = 0; u < n; u++)
      make_set(u);
  }

  void make_set(int u) {
    parents[u] = u;
    sizes[u]   = 1;
  }

  int find_set(int u) {
    if (parents[u] == u)
      return u;
    else {
      parents[u] = find_set(parents[u]);
      return parents[u];
    }
  }

  bool unite(int x, int y) {
    int x_root{find_set(x)}, y_root{find_set(y)};

    if (x_root == y_root)
      return false;

    if (sizes[x_root] < sizes[y_root])
      std::swap(x_root, y_root);

    sizes[x_root] += sizes[y_root];
    parents[y_root] = x_root;

    return true;
  }
};
