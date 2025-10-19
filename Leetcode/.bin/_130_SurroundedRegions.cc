#include <vector>

class Solution
{
private:
  int dx_[4] = {-1, 0, 1, 0};
  int dy_[4] = {0, 1, 0, -1};
  bool surrounded_{true};
  std::vector<std::vector<bool>> visited_;
  std::vector<std::vector<bool>> visited_replace_;

  void dfs_visit_(const std::vector<std::vector<char>> &board, int y, int x,
                  int n, int m)
  {
    if (y >= n || y < 0 || x >= m || x < 0)
    {
      surrounded_ = false;
      return;
    }

    if (board[y][x] == 'X' || visited_[y][x])
      return;

    visited_[y][x] = true;

    for (int i = 0; i < 4; i++)
      dfs_visit_(board, y + dy_[i], x + dx_[i], n, m);
  }

  void dfs_replace_(std::vector<std::vector<char>> &board, int y, int x, int n,
                    int m)
  {
    if (y >= n || y < 0 || x >= m || x < 0 || board[y][x] == 'X' ||
        visited_replace_[y][x])
      return;

    board[y][x]            = 'X';
    visited_replace_[y][x] = true;

    for (int i = 0; i < 4; i++)
      dfs_replace_(board, y + dy_[i], x + dx_[i], n, m);
  }

public:
  void solve(std::vector<std::vector<char>> &board)
  {
    int n{static_cast<int>(board.size())}, m{static_cast<int>(board[0].size())};

    visited_ = std::vector<std::vector<bool>>(n, std::vector<bool>(m, false));
    visited_replace_ =
        std::vector<std::vector<bool>>(n, std::vector<bool>(m, false));

    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
      {
        if (board[y][x] == 'O' && !visited_[y][x])
        {
          dfs_visit_(board, y, x, n, m);
          if (surrounded_)
            dfs_replace_(board, y, x, n, m);
          surrounded_ = true;
        }
      }
  }
};
