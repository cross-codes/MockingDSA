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
  int largestIsland(std::vector<std::vector<int>> &grid)
  {
    int n        = static_cast<int>(grid.size());
    auto get_idx = [&n](int y, int x) -> int { return n * y + x; };

    DisjointSetForest dsu(n * n);

    auto valid = [&n](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < n;
    };

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    for (int y = 0; y < n; y++)
      for (int x = 0; x < n; x++)
      {
        if (grid[y][x] == 1)
          for (int i = 0; i < 4; i++)
          {
            int Y{y + dy[i]}, X{x + dx[i]};
            if (valid(Y, X) && grid[Y][X] == 1)
              dsu.unite(get_idx(y, x), get_idx(Y, X));
          }
      }

    int gmx{};
    for (int y = 0; y < n; y++)
      for (int x = 0; x < n; x++)
        if (grid[y][x] == 1)
          gmx = std::max(gmx, dsu.sizes[dsu.find_set(get_idx(y, x))]);

    auto contains = [](std::vector<int> check, int target) -> bool {
      for (int e : check)
        if (e == target)
          return true;

      return false;
    };

    for (int y = 0; y < n; y++)
      for (int x = 0; x < n; x++)
      {
        if (grid[y][x] == 0)
        {
          std::vector<int> repr{};
          int ns{1};
          for (int i = 0; i < 4; i++)
          {
            int Y{y + dy[i]}, X{x + dx[i]};
            if (valid(Y, X) && grid[Y][X] == 1)
            {
              int set = dsu.find_set(get_idx(Y, X));
              if (!contains(repr, set))
              {
                ns += dsu.sizes[set];
                repr.push_back(set);
              }
            }
          }
          gmx = std::max(gmx, ns);
        }
      }

    return gmx;
  }
};
