#include <cstring>
#include <queue>
#include <vector>

class Solution
{
private:
  int dx_[4] = {1, 0, -1, 0};
  int dy_[4] = {0, -1, 0, 1};

  auto check_grid(std::vector<std::vector<int>> &grid) -> bool
  {
    int n{static_cast<int>(grid.size())};
    int m{static_cast<int>(grid[0].size())};

    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
        if (grid[y][x] == 1)
          return false;

    return true;
  }

public:
  int orangesRotting(std::vector<std::vector<int>> &grid)
  {
    int n{static_cast<int>(grid.size())};
    int m{static_cast<int>(grid[0].size())};

    bool visited[n][m];
    std::memset(visited, false, sizeof(visited));

    bool res = check_grid(grid);

    if (res)
      return 0;

    std::queue<std::pair<int, int>> rotting{};
    std::queue<std::pair<int, int>> process{};
    for (int y = 0; y < n; y++)
    {
      for (int x = 0; x < m; x++)
      {
        if (grid[y][x] == 2)
        {
          rotting.emplace(x, y);
        }
      }
    }

    int time_{1};
    while (!rotting.empty())
    {
      std::swap(process, rotting);
      while (!process.empty())
      {
        auto pair = process.front();
        process.pop();

        int X{pair.first}, Y{pair.second};
        for (int i = 0; i < 4; i++)
        {
          int nx{X + dx_[i]}, ny{Y + dy_[i]};
          if (nx >= m || nx < 0 || ny >= n || ny < 0 || visited[ny][nx] ||
              grid[ny][nx] != 1)
            continue;

          visited[ny][nx] = true;
          rotting.emplace(nx, ny);
          grid[ny][nx] = 2;
        }
      }

      res = check_grid(grid);
      if (res)
        break;
      time_ += 1;
    }

    return res ? time_ : -1;
  }
};
