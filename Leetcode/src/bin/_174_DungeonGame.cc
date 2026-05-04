#include <climits>
#include <vector>

class Solution
{
public:
  int calculateMinimumHP(std::vector<std::vector<int>> &dungeon)
  {
    int n = static_cast<int>(dungeon.size());
    int m = static_cast<int>(dungeon[0].size());

    // min health needed to survive at end from i, j
    // mh(i, j) = mh(i + 1, j) - h(i, j);
    int mh[n][m];

    mh[n - 1][m - 1] = -dungeon[n - 1][m - 1] + 1;

    for (int x = m - 2; x >= 0; x--)
    {
      if (mh[n - 1][x + 1] <= 0)
        mh[n - 1][x] = 1 - dungeon[n - 1][x];
      else
        mh[n - 1][x] = mh[n - 1][x + 1] - dungeon[n - 1][x];
    }

    for (int y = n - 2; y >= 0; y--)
      for (int x = m - 1; x >= 0; x--)
      {
        int right{INT_MAX}, down{mh[y + 1][x]};
        if (x < m - 1)
          right = mh[y][x + 1];

        if (std::min(down, right) <= 0)
          mh[y][x] = 1 - dungeon[y][x];
        else
          mh[y][x] = std::min(right, down) - dungeon[y][x];
      }

    return mh[0][0] <= 0 ? 1 : mh[0][0];
  }
};
