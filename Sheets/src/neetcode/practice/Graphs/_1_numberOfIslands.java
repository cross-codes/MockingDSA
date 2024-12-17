package neetcode.practice.Graphs;

class Solution {
  public void dfs(int i, int j, char[][] grid, int numRows, int numColumns, Procedure proc) {
    if (i < 0 || i >= numRows || j < 0 || j >= numColumns || grid[i][j] == '0')
      return;

    proc.run(grid, i, j);

    this.dfs(i + 1, j, grid, numRows, numColumns, proc);
    this.dfs(i - 1, j, grid, numRows, numColumns, proc);
    this.dfs(i, j + 1, grid, numRows, numColumns, proc);
    this.dfs(i, j - 1, grid, numRows, numColumns, proc);
  }

  public int numIslands(char[][] grid) {
    int numRows = grid.length, numColumns = grid[0].length;
    int numIslands = 0;

    Procedure proc = (matrix, i, j) -> matrix[i][j] = '0';

    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        if (grid[i][j] == '1') {
          this.dfs(i, j, grid, numRows, numColumns, proc);
          numIslands++;
        }
      }
    }

    return numIslands;
  }
}

interface Procedure {
  public void run(char[][] grid, int i, int j);
}