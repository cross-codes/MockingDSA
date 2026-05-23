#include <climits>
#include <cstdint>
#include <vector>

class Solution
{
public:
  int maximumAmount(std::vector<std::vector<int>> &coins)
  {
    int n = static_cast<int>(coins.size());
    int m = static_cast<int>(coins[0].size());

    int64_t mx[n][m][3];
    mx[0][0][2] = coins[0][0];
    mx[0][0][1] = coins[0][0] < 0 ? 0 : INT_MIN;
    mx[0][0][0] = INT_MIN;

    for (int k = 2; k >= 0; k--)
      for (int x = 1; x < m; x++)
      {
        if (k == 2)
          mx[0][x][k] = mx[0][x - 1][k] + coins[0][x];
        else
        {
          mx[0][x][k] = mx[0][x - 1][k] + coins[0][x];
          if (coins[0][x] < 0)
            mx[0][x][k] = std::max(mx[0][x][k], mx[0][x - 1][k + 1]);
        }
      }

    for (int k = 2; k >= 0; k--)
      for (int y = 1; y < n; y++)
      {
        if (k == 2)
          mx[y][0][k] = mx[y - 1][0][k] + coins[y][0];
        else
        {
          mx[y][0][k] = mx[y - 1][0][k] + coins[y][0];
          if (coins[y][0] < 0)
            mx[y][0][k] = std::max(mx[y][0][k], mx[y - 1][0][k + 1]);
        }
      }

    for (int k = 2; k >= 0; k--)
      for (int y = 1; y < n; y++)
        for (int x = 1; x < m; x++)
        {
          if (k == 2)
            mx[y][x][k] =
                std::max(mx[y - 1][x][k], mx[y][x - 1][k]) + coins[y][x];
          else
          {
            mx[y][x][k] =
                std::max(mx[y - 1][x][k], mx[y][x - 1][k]) + coins[y][x];
            if (coins[y][x] < 0)
            {
              mx[y][x][k] = std::max(mx[y - 1][x][k + 1], mx[y][x][k]);
              mx[y][x][k] = std::max(mx[y][x - 1][k + 1], mx[y][x][k]);
            }
          }
        }

    return std::max(
        {mx[n - 1][m - 1][0], mx[n - 1][m - 1][1], mx[n - 1][m - 1][2]});
  }
};
