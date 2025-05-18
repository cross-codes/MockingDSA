#include <vector>

class Solution
{
private:
  int num_rows_, num_cols_;
  int curr_dist_{1};

  void dfs_(int row, int col, std::vector<std::vector<int>> &grid)
  {
    curr_dist_ += 1;

    if (row >= num_rows_ || row < 0 || col >= num_cols_ || col < 0 ||
        grid[row][col] <= 0)
    {
      curr_dist_ -= 1;
      return;
    }

    grid[row][col] = std::min(grid[row][col], curr_dist_);
    dfs_(row + 1, col, grid);
    dfs_(row - 1, col, grid);
    dfs_(row, col + 1, grid);
    dfs_(row, col - 1, grid);
  }

public:
  void islandsAndTreasure(std::vector<std::vector<int>> &grid)
  {
    num_rows_ = static_cast<int>(grid.size());
    num_cols_ = static_cast<int>(grid[0].size());

    for (int y = 0; y < num_rows_; y++)
      for (int x = 0; x < num_cols_; x++)
        if (grid[y][x] == 0)
        {
          curr_dist_ = 1;
          dfs_(y + 1, x, grid);
          curr_dist_ = 1;

          dfs_(y - 1, x, grid);
          curr_dist_ = 1;

          dfs_(y, x + 1, grid);
          curr_dist_ = 1;

          dfs_(y, x - 1, grid);
        }
  }
};
