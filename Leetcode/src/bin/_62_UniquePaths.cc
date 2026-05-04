#include <array>

class Solution
{
public:
  int uniquePaths(int m, int n)
  {
    std::size_t M = static_cast<std::size_t>(m),
                N = static_cast<std::size_t>(n);
    std::array<std::array<int, 101>, 101> numPaths;

    numPaths[1][1] = 1;
    for (std::size_t y = 1UZ; y <= M; y++)
      for (std::size_t x = 1UZ; x <= N; x++)
        if (!(y == 1UZ && x == 1UZ))
          numPaths[y][x] = numPaths[y - 1][x] + numPaths[y][x - 1];

    return numPaths[m][n];
  }
};
