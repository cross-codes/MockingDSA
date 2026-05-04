package collections.ranged;

public class Prefix2DGenerator {
  private long[][] prefix2D;

  public Prefix2DGenerator(long[][] grid) {
    int n = grid.length, m = grid[0].length;

    prefix2D = new long[n][m];
    long[][] vpsinc = new long[m][n];
    for (int x = 0; x < m; x++) {
      for (int y = 0; y < n; y++) {
        if (y == 0) {
          vpsinc[x][y] = grid[y][x];
        } else {
          vpsinc[x][y] = vpsinc[x][y - 1] + grid[y][x];
        }
      }
    }

    for (int y = 0; y < n; y++) {
      prefix2D[y][0] = vpsinc[0][y];
    }

    for (int y = 0; y < n; y++) {
      for (int x = 1; x < m; x++) {
        prefix2D[y][x] = prefix2D[y][x - 1] + vpsinc[x][y];
      }
    }
  }

  public long sumRegion(int y1, int x1, int y2, int x2) {
    int ax = x2, ay = y2;
    int bx = x1, by = y2;
    int cx = x2, cy = y1;
    int dx = x1, dy = y1;

    long res = prefix2D[ay][ax];

    if (bx > 0) {
      res -= prefix2D[by][bx - 1];
    }

    if (cy > 0) {
      res -= prefix2D[cy - 1][cx];
    }

    if (dx > 0 && dy > 0) {
      res += prefix2D[dy - 1][dx - 1];
    }

    return res;
  }
}
