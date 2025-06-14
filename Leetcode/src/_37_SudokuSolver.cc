#include <array>
#include <iostream>
#include <vector>

class Solution
{
public:
  void solveSudoku(std::vector<std::vector<char>> &board)
  {
    std::array<std::array<bool, 10>, 9> rows{}, cols{}, grids{};

    auto get_grid = [](int y, int x) -> int {
      if (y < 3)
      {
        if (x < 3)
          return 0;
        else if (x < 6)
          return 1;
        else
          return 2;
      }
      else if (y < 6)
      {
        if (x < 3)
          return 3;
        else if (x < 6)
          return 4;
        else
          return 5;
      }
      else
      {
        if (x < 3)
          return 6;
        else if (x < 6)
          return 7;
        else
          return 8;
      }
    };

    std::vector<std::pair<int, int>> unfilled{};
    std::vector<std::vector<char>> ans = board;

    for (int y = 0; y < 9; y++)
      for (int x = 0; x < 9; x++)
      {
        if (board[y][x] != '.')
        {
          int grid         = get_grid(y, x);
          int val          = board[y][x] - '0';
          rows[y][val]     = true;
          cols[x][val]     = true;
          grids[grid][val] = true;
        }
        else
          unfilled.emplace_back(y, x);
      }

    auto dfs = [&unfilled, &board, &rows, &cols, &grids, &ans,
                &get_grid](auto &&dfs, int idx) -> void {
      if (idx == static_cast<int>(unfilled.size()))
      {
        board = ans;
        return;
      }

      const auto &[y, x] = unfilled[idx];
      auto grid          = get_grid(y, x);

      std::vector<int> choices{};
      for (int i = 1; i <= 9; i++)
      {
        if (!cols[x][i] && !rows[y][i] && !grids[grid][i])
          choices.push_back(i);
      }

      for (const int &choice : choices)
      {
        ans[y][x]           = static_cast<char>(choice + '0');
        rows[y][choice]     = true;
        cols[x][choice]     = true;
        grids[grid][choice] = true;
        dfs(dfs, idx + 1);
        ans[y][x]           = '.';
        rows[y][choice]     = false;
        cols[x][choice]     = false;
        grids[grid][choice] = false;
      }
    };

    dfs(dfs, 0);
  }
};

int main()
{
  std::vector<std::vector<char>> board = {
      {'9', '.', '3', '.', '.', '1', '.', '.', '2'},
      {'.', '5', '.', '.', '.', '2', '.', '3', '.'},
      {'.', '.', '.', '.', '6', '8', '.', '.', '5'},
      {'8', '2', '9', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '1', '.', '.', '.', '9', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '8', '2', '6'},
      {'2', '.', '.', '7', '3', '.', '.', '.', '.'},
      {'.', '3', '.', '4', '.', '.', '.', '6', '.'},
      {'1', '.', '.', '8', '.', '.', '7', '.', '3'}};

  Solution().solveSudoku(board);
  for (auto &row : board)
  {
    for (char e : row)
      std::cout << e - '0' << " ";

    std::cout << "\n";
  }
}
