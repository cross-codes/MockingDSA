#include <numeric>
#include <unordered_set>
#include <vector>

class Solution
{
private:
  class DisjointSetForest
  {
  public:
    std::vector<int> sizes, parents;

    DisjointSetForest(int n) : sizes(n), parents(n)
    {
      std::iota(parents.begin(), parents.end(), 0);
      std::fill(sizes.begin(), sizes.end(), 1);
    }

    auto find_set(int u) -> int
    {
      if (parents[u] == u)
        return u;
      else
        return parents[u] = find_set(parents[u]);
    }

    auto unite(int x, int y) -> bool
    {
      int x_root = find_set(x);
      int y_root = find_set(y);

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
  int numEnclaves(std::vector<std::vector<int>> &grid)
  {
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());
    DisjointSetForest dsu(n * m);

    auto get_idx = [&m](int y, int x) -> int { return m * y + x; };

    auto valid   = [&n, &m](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < m;
    };

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    int ocnt{};
    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
      {
        if (grid[y][x] == 1)
        {
          ocnt += 1;
          for (int i = 0; i < 4; i++)
          {
            int X{x + dx[i]}, Y{y + dy[i]};
            if (valid(Y, X) && grid[Y][X] == 1)
            {
              dsu.unite(get_idx(y, x), get_idx(Y, X));
            }
          }
        }
      }

    int cnt{};
    std::unordered_set<int> seen{};
    for (int x = 0; x < m; x++)
    {
      if (grid[0][x] == 1)
      {
        int set = dsu.find_set(get_idx(0, x));
        if (!seen.contains(set))
        {
          cnt += dsu.sizes[set];
          seen.insert(set);
        }
      }

      if (grid[n - 1][x] == 1)
      {
        int set = dsu.find_set(get_idx(n - 1, x));
        if (!seen.contains(set))
        {
          cnt += dsu.sizes[set];
          seen.insert(set);
        }
      }
    }

    for (int y = 0; y < n; y++)
    {
      if (grid[y][0] == 1)
      {
        int set = dsu.find_set(get_idx(y, 0));
        if (!seen.contains(set))
        {
          cnt += dsu.sizes[set];
          seen.insert(set);
        }
      }

      if (grid[y][m - 1] == 1)
      {

        int set = dsu.find_set(get_idx(y, m - 1));
        if (!seen.contains(set))
        {
          cnt += dsu.sizes[set];
          seen.insert(set);
        }
      }
    }

    return ocnt - cnt;
  }
};
