package neetcode.practice.Graphs;

class Solution {
  public int numIslands = 0;

  public void dfs(int i, int j, char[][] grid, int numRows, int numColumns) {
    if (i < 0 || i >= numRows || j < 0 || j >= numColumns || grid[i][j] == '0')
      return;

    grid[i][j] = '0';
    dfs(i + 1, j, grid, numRows, numColumns);
    dfs(i - 1, j, grid, numRows, numColumns);
    dfs(i, j + 1, grid, numRows, numColumns);
    dfs(i, j - 1, grid, numRows, numColumns);
  }

  public int numIslands(char[][] grid) {
    int numRows = grid.length, numColumns = grid[0].length;

    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        if (grid[i][j] == '1') {
          dfs(i, j, grid, numRows, numColumns);
          this.numIslands++;
        }
      }
    }

    return this.numIslands;
  }
}