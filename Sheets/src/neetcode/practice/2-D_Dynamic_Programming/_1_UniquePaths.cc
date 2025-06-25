#include <cstring>

class Solution
{
public:
  int uniquePaths(int m, int n)
  {
    int ways[m][n];
    for (int i = 0; i < m; i++)
      std::memset(ways[i], 0x00, sizeof(int) * n);

    for (int x = 0; x < n; x++)
      ways[0][x] = 1;

    for (int y = 0; y < m; y++)
      ways[y][0] = 1;

    for (int y = 1; y < m; y++)
      for (int x = 1; x < n; x++)
        ways[y][x] = ways[y - 1][x] + ways[y][x - 1];

    return ways[m - 1][n - 1];
  }
};
