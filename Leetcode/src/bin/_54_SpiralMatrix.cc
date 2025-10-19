#include <vector>

class Solution
{
private:
  void dfs_(int row, int col, int r, int c, int dr, int dc,
            std::vector<std::vector<int>> &matrix, std::vector<int> &res)
  {
    if (row == 0 || col == 0)
      return;

    for (int i = 0; i < col; i++)
    {
      r += dr;
      c += dc;
      res.push_back(matrix[r][c]);
    }

    dfs_(col, row - 1, r, c, dc, -dr, matrix, res);
  }

public:
  std::vector<int> spiralOrder(std::vector<std::vector<int>> &matrix)
  {
    int m = static_cast<int>(matrix.size()),
        n = static_cast<int>(matrix[0].size());

    std::vector<int> res;

    dfs_(m, n, 0, -1, 0, 1, matrix, res);
    return res;
  }
};
