#include <string>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<std::string>> solveNQueens(int n)
  {
    std::vector<std::vector<std::string>> res{};

    std::vector<bool> column(n, false);
    std::vector<bool> diag1(n << 1, false), diag2(n << 1, false);

    auto dfs = [&res, &n, &column, &diag1, &diag2](
                   auto &&dfs, int y, std::vector<std::string> &board) -> void {
      if (y == n)
      {
        res.push_back(board);
        return;
      }

      for (int x = 0; x < n; x++)
      {
        if (column[x] || diag1[x + y] || diag2[x - y + n - 1])
          continue;

        column[x] = diag1[x + y] = diag2[x - y + n - 1] = true;
        board[y][x]                                     = 'Q';
        dfs(dfs, y + 1, board);
        column[x] = diag1[x + y] = diag2[x - y + n - 1] = false;
        board[y][x]                                     = '.';
      }
    };

    std::vector<std::string> board(n, std::string(n, '.'));
    dfs(dfs, 0, board);
    return res;
  }
};
