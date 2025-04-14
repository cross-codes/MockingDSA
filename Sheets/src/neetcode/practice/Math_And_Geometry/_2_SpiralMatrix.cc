#include <vector>

class Solution
{
private:
  std::vector<int> res{};

  void spiral(std::vector<std::vector<int>> &matrix, int row_number)
  {
    int y_max = static_cast<int>(matrix.size()),
        x_max = static_cast<int>(matrix[0].size());
    for (int x = row_number; x < x_max - row_number; x++)
      res.push_back(matrix[row_number][x]);

    for (int y = row_number; y < y_max - row_number; y++)
      res.push_back(matrix[y][x_max - row_number]);

    for (int x = x_max - row_number; x > row_number; x--)
      res.push_back(matrix[y_max - row_number][x]);

    for (int y = y_max - row_number; y > row_number; y--)
      res.push_back(matrix[y][row_number]);
  }

public:
  std::vector<int> spiralOrder(std::vector<std::vector<int>> &matrix)
  {
    int num_rows = static_cast<int>(matrix.size());
    for (int i = 0; i < (num_rows >> 1); i++)
      spiral(matrix, i);

    return res;
  }
};
