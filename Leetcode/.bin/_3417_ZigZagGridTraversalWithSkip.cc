#include <vector>

class Solution
{
public:
  std::vector<int> zigzagTraversal(std::vector<std::vector<int>> &grid)
  {
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());

    std::vector<int> res{};
    int y{};
    bool skip{};
    while (y != n)
    {
      if (!(y & 1))
      {
        for (int x = 0; x < m; x++)
        {
          if (!skip)
            res.push_back(grid[y][x]);
          skip = !skip;
        }
        y += 1;
      }
      else
      {
        for (int x = m - 1; x >= 0; x--)
        {
          if (!skip)
            res.push_back(grid[y][x]);
          skip = !skip;
        }

        y += 1;
      }
    }

    return res;
  }
};
