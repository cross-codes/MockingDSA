#include <bitset>
#include <cstring>
#include <queue>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> pacificAtlantic(
      std::vector<std::vector<int>> &heights)
  {
    int n        = static_cast<int>(heights.size());
    int m        = static_cast<int>(heights[0].size());

    auto get_idx = [&m](int y, int x) -> int { return y * m + x; };

    auto valid   = [&n, &m](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < m;
    };

    std::bitset<40001> pacific{}, atlantic{};
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    bool visited[n][m];
    std::memset(visited, false, sizeof visited);

    std::queue<std::pair<int, int>> queue{};
    for (int y = 0; y < n; y++)
    {
      queue.emplace(y, 0);
      pacific.set(get_idx(y, 0));
      visited[y][0] = true;
    }

    for (int x = 0; x < m; x++)
    {
      queue.emplace(0, x);
      pacific.set(get_idx(0, x));
      visited[0][x] = true;
    }

    while (!queue.empty())
    {
      auto [y, x] = queue.front();
      queue.pop();

      for (int i = 0; i < 4; i++)
      {
        int Y{y + dy[i]}, X{x + dx[i]};
        if (valid(Y, X) && !visited[Y][X] && heights[Y][X] >= heights[y][x])
        {
          visited[Y][X] = true;
          pacific.set(get_idx(Y, X));
          queue.emplace(Y, X);
        }
      }
    }

    std::memset(visited, false, sizeof visited);

    for (int y = 0; y < n; y++)
    {
      queue.emplace(y, m - 1);
      atlantic.set(get_idx(y, m - 1));
      visited[y][m - 1] = true;
    }

    for (int x = 0; x < m; x++)
    {
      queue.emplace(n - 1, x);
      atlantic.set(get_idx(n - 1, x));
      visited[n - 1][x] = true;
    }

    while (!queue.empty())
    {
      auto [y, x] = queue.front();
      queue.pop();

      for (int i = 0; i < 4; i++)
      {
        int Y{y + dy[i]}, X{x + dx[i]};
        if (valid(Y, X) && !visited[Y][X] && heights[Y][X] >= heights[y][x])
        {
          visited[Y][X] = true;
          atlantic.set(get_idx(Y, X));
          queue.emplace(Y, X);
        }
      }
    }

    std::bitset<40001> result = pacific & atlantic;

    std::vector<std::vector<int>> res{};
    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
      {
        if (result[get_idx(y, x)])
          res.push_back({y, x});
      }

    return res;
  }
};
