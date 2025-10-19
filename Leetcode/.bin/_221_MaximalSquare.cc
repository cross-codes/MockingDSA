#include <cstring>
#include <vector>

class Solution
{
public:
  int maximalSquare(std::vector<std::vector<char>> &matrix)
  {
    int n = static_cast<int>(matrix.size());
    int m = static_cast<int>(matrix[0].size());

    int mxs[n][m];
    std::memset(mxs, 0x00, sizeof(mxs));

    int mx{};
    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
      {
        if (matrix[y][x] == '1')
        {
          int up{}, left{}, diag_left{};
          if (y > 0)
            up = mxs[y - 1][x];
          if (x > 0)
            left = mxs[y][x - 1];
          if (y > 0 && x > 0)
            diag_left = mxs[y - 1][x - 1];

          mxs[y][x] = 1 + std::min(diag_left, std::min(up, left));
          mx        = std::max(mx, mxs[y][x] * mxs[y][x]);
        }
      }

    return mx;
  }
};
