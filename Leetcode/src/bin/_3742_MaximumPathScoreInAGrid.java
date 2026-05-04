import java.util.Arrays;

class Solution {
  public int maxPathScore(int[][] grid, int k) {
    int n = grid.length, m = grid[0].length;
    int[][][] mxs = new int[n][m][k + 1];
    for (int y = 0; y < n; y++) {
      for (int x = 0; x < m; x++) {
        Arrays.fill(mxs[y][x], -1);
      }
    }

    IntToIntFunction costFunction = (val) -> {
      switch (val) {
        case 0:
          return 0;
        default:
          return 1;
      }
    };

    mxs[0][0][costFunction.apply(grid[0][0])] = grid[0][0];
    for (int y = 1; y < n; y++) {
      for (int i = 0; i <= k; i++) {
        int cost = costFunction.apply(grid[y][0]);
        if (i - cost >= 0 && mxs[y - 1][0][i - cost] != -1) {
          mxs[y][0][i] = mxs[y - 1][0][i - cost] + grid[y][0];
        }
      }
    }

    for (int x = 1; x < m; x++) {
      for (int i = 0; i <= k; i++) {
        int cost = costFunction.apply(grid[0][x]);
        if (i - cost >= 0 && mxs[0][x - 1][i - cost] != -1) {
          mxs[0][x][i] = mxs[0][x - 1][i - cost] + grid[0][x];
        }
      }
    }

    for (int y = 1; y < n; y++) {
      for (int x = 1; x < m; x++) {
        for (int i = 0; i <= k; i++) {
          int cost = costFunction.apply(grid[y][x]);
          if (i - cost >= 0) {
            int up = mxs[y - 1][x][i - cost];
            int left = mxs[y][x - 1][i - cost];
            if (up != -1 || left != -1) {
              mxs[y][x][i] = Math.max(up, left) + grid[y][x];
            }
          }
        }
      }
    }

    int gmx = -1;
    for (int i = 0; i <= k; i++) {
      gmx = Math.max(gmx, mxs[n - 1][m - 1][i]);
    }

    return gmx;
  }

  @FunctionalInterface
  interface IntToIntFunction {
    int apply(int arg);
  }
}
