#include <cstring>
#include <vector>

class Solution
{
private:
  bool visited_[50][50];
  int num_rows_, num_cols_;
  int max_cnt_{}, current_cnt_{};

  int dx[4] = {1, 0, -1, 0};
  int dy[4] = {0, 1, 0, -1};

  void dfs_(int row, int col, std::vector<std::vector<int>> &grid)
  {
    if (row >= num_rows_ || row < 0 || col >= num_cols_ || col < 0 ||
        visited_[row][col] || grid[row][col] == 0)
      return;

    visited_[row][col] = true;
    current_cnt_ += 1;

    for (int i = 0; i < 4; i++)
      dfs_(row + dx[i], col + dy[i], grid);
  }

public:
  int maxAreaOfIsland(std::vector<std::vector<int>> &grid)
  {
    num_rows_ = static_cast<int>(grid.size());
    num_cols_ = static_cast<int>(grid[0].size());

    std::memset(visited_, false, sizeof(visited_));

    for (int y = 0; y < num_rows_; y++)
      for (int x = 0; x < num_cols_; x++)
        if (!visited_[y][x] && grid[y][x] == 1)
        {
          current_cnt_ = 0;
          dfs_(y, x, grid);
          max_cnt_ = std::max(max_cnt_, current_cnt_);
        }

    return max_cnt_;
  }
};
