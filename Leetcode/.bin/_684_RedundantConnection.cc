#include <algorithm>
#include <vector>

class Solution
{
private:
  struct DisjointSetForest
  {
  public:
    std::vector<int> sizes, parents;

    DisjointSetForest(int n) : sizes(n), parents(n)
    {
      for (int u = 0; u < n; u++)
        make_set(u);
    }

    void make_set(int u)
    {
      parents[u] = u;
      sizes[u]   = 1;
    }

    int find_set(int u)
    {
      if (parents[u] == u)
        return u;
      else
      {
        parents[u] = find_set(parents[u]);
        return parents[u];
      }
    }

    bool unite(int x, int y)
    {
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

public:
  std::vector<int> findRedundantConnection(std::vector<std::vector<int>> &edges)
  {
    int n{};
    for (const auto &vec : edges)
    {
      int a = vec[0], b = vec[1];
      n = std::max(a, std::max(b, n));
    }

    DisjointSetForest dsu(n);

    for (const auto &vec : edges)
    {
      int a = vec[0] - 1, b = vec[1] - 1;
      if (dsu.find_set(a) == dsu.find_set(b))
        return vec;
      else
        dsu.unite(a, b);
    }

    __builtin_unreachable();
  }
};
