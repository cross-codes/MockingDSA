#include <vector>

class Solution
{
public:
  bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
  {
    int num_rows = static_cast<int>(matrix.size()),
        num_cols = static_cast<int>(matrix[0].size());

    int L{-1}, R{num_rows * num_cols};
    while (R - L > 1)
    {
      int M = L + ((R - L) >> 1);
      int Y = M / num_cols, X = M % num_cols;
      if (target < matrix[Y][X])
        R = M;
      else
        L = M;
    }

    if (L == -1)
      return false;
    else
      return matrix[L / num_cols][L % num_cols] == target;
  }
};
