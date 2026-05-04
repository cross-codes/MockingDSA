#include <cstring>
#include <queue>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>> &mat)
  {
    int n = static_cast<int>(mat.size());
    int m = static_cast<int>(mat[0].size());

    std::queue<std::pair<int, std::pair<int, int>>> queue{};
    std::vector<std::vector<int>> res(n, std::vector<int>(m, 0));

    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
        if (mat[y][x] == 0)
        {
          queue.emplace(0, std::make_pair(y, x));
          res[y][x] = 0;
        }

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    bool processed[n][m];
    std::memset(processed, false, sizeof processed);

    auto valid = [&n, &m](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < m;
    };

    while (!queue.empty())
    {
      auto d      = queue.front().first;
      auto [y, x] = queue.front().second;
      queue.pop();

      for (int i = 0; i < 4; i++)
      {
        int Y{y + dy[i]}, X{x + dx[i]};
        if (valid(Y, X))
        {
          if (mat[Y][X] == 1 && !processed[Y][X])
          {
            queue.emplace(d + 1, std::make_pair(Y, X));
            res[Y][X]       = d + 1;
            processed[Y][X] = true;
          }
        }
      }
    }

    return res;
  }
};
