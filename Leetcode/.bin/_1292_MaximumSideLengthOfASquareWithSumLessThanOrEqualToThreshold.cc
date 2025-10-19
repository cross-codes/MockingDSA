#include <numeric>
#include <vector>

class Solution
{
public:
  int maxSideLength(std::vector<std::vector<int>> &mat, int threshold)
  {
    int n = static_cast<int>(mat.size());
    int m = static_cast<int>(mat[0].size());

    int prefix[301][301], vpsinc[301][301];
    prefix[0][0] = mat[0][0];

    for (int x = 1; x < m; x++)
    {
      prefix[0][x] = prefix[0][x - 1] + mat[0][x];
      vpsinc[x][0] = mat[0][x];
    }

    for (int y = 1; y < n; y++)
      prefix[y][0] = prefix[y - 1][0] + mat[y][0];

    for (int x = 0; x < m; x++)
      for (int y = 1; y < n; y++)
        vpsinc[x][y] = vpsinc[x][y - 1] + mat[y][x];

    for (int y = 1; y < n; y++)
      for (int x = 1; x < m; x++)
        prefix[y][x] = prefix[y][x - 1] + vpsinc[x][y];

    auto rs = [&prefix](int y1, int y2, int x1, int x2) -> int {
      int base = prefix[y2][x2];

      if (y1 > 0)
        base -= prefix[y1 - 1][x2];
      if (x1 > 0)
        base -= prefix[y2][x1 - 1];

      if (y1 > 0 && x1 > 0)
        base += prefix[y1 - 1][x1 - 1];

      return base;
    };

    // region of side length l with sum <= threshold
    auto pred = [&rs, &threshold, &n, &m](int l) -> bool {
      for (int y = 0; y <= n - l; y++)
        for (int x = 0; x <= m - l; x++)
        {
          int y1 = y, x1 = x, y2 = y + l - 1, x2 = x + l - 1;
          if (rs(y1, y2, x1, x2) <= threshold)
            return true;
        }

      return false;
    };

    int L{}, R{std::min(n, m) + 1};
    while (R - L > 1)
    {
      int M              = std::midpoint(L, R);
      (!pred(M) ? R : L) = M;
    }

    return L;
  }
};
