#include <cstring>
#include <vector>

class NumMatrix
{
private:
  std::vector<std::vector<int>> prefix_2D;

public:
  NumMatrix(std::vector<std::vector<int>> &matrix)
  {
    int n = static_cast<int>(matrix.size());
    int m = static_cast<int>(matrix[0].size());

    prefix_2D.resize(n, std::vector<int>(m, 0));

    int vpsinc[m][n];
    std::memset(vpsinc, 0x00, sizeof(vpsinc));
    for (int x = 0; x < m; x++)
      for (int y = 0; y < n; y++)
      {
        if (y == 0)
          vpsinc[x][y] = matrix[y][x];
        else
          vpsinc[x][y] = vpsinc[x][y - 1] + matrix[y][x];
      }

    for (int y = 0; y < n; y++)
      prefix_2D[y][0] = vpsinc[0][y];

    for (int y = 0; y < n; y++)
      for (int x = 1; x < m; x++)
        prefix_2D[y][x] = prefix_2D[y][x - 1] + vpsinc[x][y];
  }

  int sumRegion(int row1, int col1, int row2, int col2)
  {
    int ax = col2, ay = row2;
    int bx = col1, by = row2;
    int cx = col2, cy = row1;
    int dx = col1, dy = row1;

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
