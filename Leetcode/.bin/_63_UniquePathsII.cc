#include <array>
#include <vector>

class Solution
{
public:
  int uniquePathsWithObstacles(std::vector<std::vector<int>> &obstacleGrid)
  {
    std::ptrdiff_t M = obstacleGrid.size(), N = obstacleGrid[0].size();
    std::array<std::array<int, 101>, 101> numPaths;

    numPaths[1][1] = (obstacleGrid[0][0] == 0 ? 1 : 0);
    if (numPaths[1][1] == 0 || obstacleGrid[M - 1][N - 1] == 1)
      return 0;

    for (std::ptrdiff_t y = 1Z; y <= M; y++)
      for (std::ptrdiff_t x = 1Z; x <= N; x++)
        if (!(y == 1Z && x == 1Z))
        {
          int up{numPaths[y - 1][x]}, left{numPaths[y][x - 1]};
          if (y >= 2Z)
            up = (obstacleGrid[y - 2][x - 1] == 0 ? numPaths[y - 1][x] : 0);
          if (x >= 2Z)
            left = (obstacleGrid[y - 1][x - 2] == 0 ? numPaths[y][x - 1] : 0);

          numPaths[y][x] = up + left;
        }

    return numPaths[M][N];
  }
};
