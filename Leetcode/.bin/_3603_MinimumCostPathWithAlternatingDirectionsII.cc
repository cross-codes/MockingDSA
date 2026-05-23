#include <cstdint>
#include <vector>

class Solution
{
public:
  int64_t minCost(int n, int m, std::vector<std::vector<int>> &waitCost)
  {
    int64_t mnc[n][m];
    mnc[0][0] = 0;

    for (int x = 1; x < m; x++)
      mnc[0][x] = mnc[0][x - 1] + (x + 1) + waitCost[0][x];

    for (int y = 1; y < n; y++)
      mnc[y][0] = mnc[y - 1][0] + (y + 1) + waitCost[y][0];

    for (int y = 1; y < n; y++)
      for (int x = 1; x < m; x++)
      {
        int64_t cell_wait = waitCost[y][x] + (y + 1) * (x + 1);
        int64_t left      = mnc[y][x - 1] + cell_wait;
        int64_t up        = mnc[y - 1][x] + cell_wait;
        mnc[y][x]         = std::min(left, up);
      }

    return 1 + mnc[n - 1][m - 1] - waitCost[n - 1][m - 1];
  }
};
