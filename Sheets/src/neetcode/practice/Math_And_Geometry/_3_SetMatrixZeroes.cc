#include <vector>

class Solution
{
public:
  void setZeroes(std::vector<std::vector<int>> &matrix)
  {
    std::vector<int> marked_rows{}, marked_cols{};
    int num_rows = static_cast<int>(matrix.size());

    for (int y = 0; y < num_rows; y++)
    {
      const auto &vec = matrix[y];
      int size        = static_cast<int>(vec.size());
      bool row_marked{};
      for (int x = 0; x < size; x++)
      {
        if (vec[x] == 0)
        {
          if (!row_marked)
          {
            marked_rows.push_back(y);
            row_marked = true;
          }
          marked_cols.push_back(x);
        }
      }
    }

    for (int row : marked_rows)
      for (int &elem : matrix[row])
        elem = 0;

    for (int col : marked_cols)
      for (int i = 0; i < num_rows; i++)
        matrix[i][col] = 0;
  }
};
