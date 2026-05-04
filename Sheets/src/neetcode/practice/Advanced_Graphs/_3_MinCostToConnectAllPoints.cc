#include <algorithm>
#include <cstdlib>
#include <vector>

class Solution
{
private:
  struct DisjointSetForest
  {
  private:
    std::vector<int> sizes_, parents_;

  public:
    DisjointSetForest(int n) : sizes_(n), parents_(n)
    {
      for (int u = 0; u < n; u++)
        make_set(u);
    }

    void make_set(int u)
    {
      parents_[u] = u;
      sizes_[u]   = 1;
    }

    int find_set(int u)
    {
      if (parents_[u] == u)
        return u;
      else
      {
        parents_[u] = find_set(parents_[u]);
        return parents_[u];
      }
    }

    bool unite(int x, int y)
    {
      int x_root{find_set(x)}, y_root{find_set(y)};

      if (x_root == y_root)
        return false;

      if (sizes_[x_root] < sizes_[y_root])
        std::swap(x_root, y_root);

      sizes_[x_root] += sizes_[y_root];
      parents_[y_root] = x_root;

      return true;
    }
  };

  struct Edge
  {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w)
    {
    }
  };

public:
  int minCostConnectPoints(std::vector<std::vector<int>> &points)
  {
    int n = static_cast<int>(points.size());

    DisjointSetForest dsu(n);
    std::vector<Edge> edges{};

    for (int u = 0; u < n; u++)
      for (int v = u + 1; v < n; v++)
        if (v != u)
        {
          const auto &v1 = points[u], &v2 = points[v];
          int w = std::abs(v1[0] - v2[0]) + std::abs(v1[1] - v2[1]);
          edges.emplace_back(u, v, w);
        }

    auto PAIR_ORDER = [](const Edge &a, const Edge &b) -> bool {
      return a.w < b.w;
    };

    std::sort(edges.begin(), edges.end(), PAIR_ORDER);

    int res{};
    for (const auto &[u, v, w] : edges)
    {
      if (dsu.find_set(u) != dsu.find_set(v))
      {
        res += w;
        dsu.unite(u, v);
      }
    }

    return res;
  }
};
