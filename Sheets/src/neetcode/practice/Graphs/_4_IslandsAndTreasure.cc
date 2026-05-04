#include <climits>
#include <queue>
#include <vector>

class Solution
{
private:
  int dx_[4] = {1, 0, -1, 0};
  int dy_[4] = {0, -1, 0, 1};

  void bfs(int x, int y, std::vector<std::vector<bool>> &visited,
           std::vector<std::vector<int>> &distances,
           std::vector<std::vector<int>> &grid)
  {
    int m{static_cast<int>(grid.size())};
    int n{static_cast<int>(grid[0].size())};

    std::queue<std::pair<int, int>> vertices{};
    vertices.emplace(x, y);
    distances[y][x] = 0;

    while (!vertices.empty())
    {
      auto pair = vertices.front();
      vertices.pop();
      int X{pair.first}, Y{pair.second};

      for (int i = 0; i < 4; i++)
      {
        int nx{X + dx_[i]}, ny{Y + dy_[i]};
        if (nx >= n || nx < 0 || ny >= m || ny < 0)
          continue;

        if (!visited[ny][nx] && grid[ny][nx] != -1 && grid[ny][nx] != 0)
        {
          distances[ny][nx] = distances[Y][X] + 1;
          grid[ny][nx]      = std::min(grid[ny][nx], distances[ny][nx]);
          vertices.emplace(nx, ny);
          visited[ny][nx] = true;
        }
      }
    }
  }

public:
  void islandsAndTreasure(std::vector<std::vector<int>> &grid)
  {
    int m{static_cast<int>(grid.size())};
    int n{static_cast<int>(grid[0].size())};

    for (int y = 0; y < m; y++)
    {
      for (int x = 0; x < n; x++)
      {
        if (grid[y][x] == 0)
        {
          std::vector<std::vector<bool>> visited(m,
                                                 std::vector<bool>(n, false));
          std::vector<std::vector<int>> distances(m,
                                                  std::vector<int>(n, INT_MAX));
          bfs(x, y, visited, distances, grid);
        }
      }
    }
  }
};
