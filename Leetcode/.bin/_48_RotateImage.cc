#include <algorithm>
#include <vector>

class Solution
{
private:
  auto squareTranspose(std::vector<std::vector<int>> &matrix,
                       std::size_t diagonalPos, std::size_t maxRows) -> void
  {
    if (diagonalPos == maxRows - 1)
      return;

    for (std::size_t i = diagonalPos + 1; i < maxRows; i++)
      std::swap(matrix[diagonalPos][i], matrix[i][diagonalPos]);

    squareTranspose(matrix, diagonalPos + 1, maxRows);
  }

public:
  void rotate(std::vector<std::vector<int>> &matrix)
  {
    std::size_t n = matrix.size();
    squareTranspose(matrix, 0, n);
    for (std::size_t i = 0; i < n; i++)
    {
      auto &row = matrix[i];
      std::reverse(row.begin(), row.end());
    }
  }
};
