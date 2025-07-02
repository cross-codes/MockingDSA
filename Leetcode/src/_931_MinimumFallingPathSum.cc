#include <algorithm>
#include <climits>
#include <vector>

class Solution
{
public:
  int minFallingPathSum(std::vector<std::vector<int>> &matrix)
  {
    int n = static_cast<int>(matrix.size());

    int min_sum[n][n];
    for (int x = 0; x < n; x++)
      min_sum[n - 1][x] = matrix[n - 1][x];

    for (int y = n - 2; y >= 0; y--)
      for (int x = 0; x < n; x++)
      {
        int below{min_sum[y + 1][x]}, left{INT_MAX}, right{INT_MAX};

        if (x > 0)
          left = min_sum[y + 1][x - 1];
        if (x < n - 1)
          right = min_sum[y + 1][x + 1];

        min_sum[y][x] = matrix[y][x] + std::min(below, std::min(left, right));
      }

    return *std::min_element(&min_sum[0][0], &min_sum[0][n]);
  }
};
