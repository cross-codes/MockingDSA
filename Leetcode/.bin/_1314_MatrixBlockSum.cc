#include <cstring>
#include <vector>

class Solution
{
private:
  struct Prefix2DGenerator
  {
  private:
    std::vector<std::vector<int>> prefix_2D;

  public:
    Prefix2DGenerator(std::vector<std::vector<int>> &grid)
    {
      int n = static_cast<int>(grid.size());
      int m = static_cast<int>(grid[0].size());

      prefix_2D.resize(n, std::vector<int>(m, 0));

      int vpsinc[m][n];
      std::memset(vpsinc, 0x00, sizeof(vpsinc));

      for (int x = 0; x < m; x++)
        for (int y = 0; y < n; y++)
        {
          if (y == 0)
            vpsinc[x][y] = grid[y][x];
          else
            vpsinc[x][y] = vpsinc[x][y - 1] + grid[y][x];
        }

      for (int y = 0; y < n; y++)
        prefix_2D[y][0] = vpsinc[0][y];

      for (int y = 0; y < n; y++)
        for (int x = 1; x < m; x++)
          prefix_2D[y][x] = prefix_2D[y][x - 1] + vpsinc[x][y];
    }

    int sum_region(int y1, int x1, int y2, int x2)
    {
      int ax = x2, ay = y2;
      int bx = x1, by = y2;
      int cx = x2, cy = y1;
      int dx = x1, dy = y1;

      int res{prefix_2D[ay][ax]};

      if (bx > 0)
        res -= prefix_2D[by][bx - 1];

      if (cy > 0)
        res -= prefix_2D[cy - 1][cx];

      if (dx > 0 && dy > 0)
        res += prefix_2D[dy - 1][dx - 1];

      return res;
    }
  };

public:
  std::vector<std::vector<int>> matrixBlockSum(
      std::vector<std::vector<int>> &mat, int k)
  {
    Prefix2DGenerator prefix(mat);

    int n = static_cast<int>(mat.size());
    int m = static_cast<int>(mat[0].size());

    std::vector<std::vector<int>> res(n, std::vector<int>(m, 0));

    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
      {
        int y1    = std::max(0, y - k);
        int x1    = std::max(0, x - k);
        int y2    = std::min(y + k, n - 1);
        int x2    = std::min(x + k, m - 1);

        res[y][x] = prefix.sum_region(y1, x1, y2, x2);
      }

    return res;
  }
};
