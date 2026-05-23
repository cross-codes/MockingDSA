#include <vector>

class Solution
{
public:
  int minimumTotal(std::vector<std::vector<int>> &triangle)
  {
    int n = static_cast<int>(triangle.size());
    int m = static_cast<int>(triangle.back().size());

    int min_sum[n][m];
    for (int x = 0; x < m; x++)
      min_sum[n - 1][x] = triangle[n - 1][x];

    for (int y = n - 2; y >= 0; y--)
      for (int x = 0; x < m - (n - 1 - y); x++)
        min_sum[y][x] =
            triangle[y][x] + std::min(min_sum[y + 1][x], min_sum[y + 1][x + 1]);

    return min_sum[0][0];
  }
};
