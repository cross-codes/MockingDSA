#include <cstring>
#include <vector>

class Solution
{
private:
  bool visited_[300][300];
  int num_rows_, num_cols_;

  int dx[4] = {1, 0, -1, 0};
  int dy[4] = {0, 1, 0, -1};

  void dfs_(int row, int col, std::vector<std::vector<char>> &grid)
  {
    if (row >= num_rows_ || row < 0 || col >= num_cols_ || col < 0 ||
        grid[row][col] == '0' || visited_[row][col])
      return;

    visited_[row][col] = true;

    for (int i = 0; i < 4; i++)
      dfs_(row + dx[i], col + dy[i], grid);
  }

public:
  int numIslands(std::vector<std::vector<char>> &grid)
  {
    num_rows_ = static_cast<int>(grid.size());
    num_cols_ = static_cast<int>(grid[0].size());

    std::memset(visited_, false, sizeof(visited_));

    int cnt{};
    for (int y = 0; y < num_rows_; y++)
      for (int x = 0; x < num_cols_; x++)
        if (!visited_[y][x] && grid[y][x] == '1')
        {
          cnt += 1;
          dfs_(y, x, grid);
        }

    return cnt;
  }
};
