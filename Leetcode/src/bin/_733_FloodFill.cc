#include <cstring>
#include <queue>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> floodFill(std::vector<std::vector<int>> &image,
                                          int sr, int sc, int color)
  {
    int n     = static_cast<int>(image.size());
    int m     = static_cast<int>(image[0].size());
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};

    int orig  = image[sr][sc];

    bool visited[n][m];
    std::memset(visited, false, sizeof visited);

    auto valid = [&n, &m](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < m;
    };

    std::queue<std::pair<int, int>> queue{};
    queue.emplace(sr, sc);
    visited[sr][sc] = true;
    image[sr][sc]   = color;
    while (!queue.empty())
    {
      auto [y, x] = queue.front();
      queue.pop();

      for (int i = 0; i < 4; i++)
      {
        int X{x + dx[i]}, Y{y + dy[i]};
        if (valid(Y, X) && !visited[Y][X] && image[Y][X] == orig)
        {
          image[Y][X] = color;
          queue.emplace(Y, X);
          visited[Y][X] = true;
        }
      }
    }

    return image;
  }
};
