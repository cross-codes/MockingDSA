#include <queue>
#include <stdexcept>
#include <vector>

struct Maze
{
private:
  std::vector<std::vector<std::pair<int, int>>> parents_{};
  std::vector<std::string> grid_;
  std::vector<std::vector<bool>> visited_;

  int sx_{}, sy_{}, dx_{}, dy_{};
  int n, m;

  auto is_valid_(int x, int y)
  {
    return (x < m) && (x >= 0) && (y < n) && (y >= 0) && (grid_[y][x] != '#');
  }

  auto direction_(int px, int py, int x, int y) -> char
  {
    if (px == x - 1 && py == y)
      return 'L';
    if (px == x + 1 && py == y)
      return 'R';
    if (px == x && py == y + 1)
      return 'D';
    if (px == x && py == y - 1)
      return 'U';

    __builtin_unreachable();
  }

public:
  int dx[4] = {-1, 0, 1, 0};
  int dy[4] = {0, 1, 0, -1};

  Maze(std::vector<std::string> &&grid, int sx, int sy, int dx, int dy)
      : grid_(std::move(grid)), sx_{sx}, sy_{sy}, dx_{dx}, dy_{dy}
  {
    if (grid_.empty() || grid_[0].empty())
      throw std::runtime_error("Grid is empty or has empty rows.");

    n        = static_cast<int>(grid_.size());
    m        = static_cast<int>(grid_[0].size());
    parents_ = std::vector<std::vector<std::pair<int, int>>>(
        n, std::vector<std::pair<int, int>>(m, {-1, -1}));
    visited_ = std::vector<std::vector<bool>>(n, std::vector<bool>(m, false));
  }

  void bfs()
  {
    std::queue<std::pair<int, int>> queue{};
    queue.emplace(sx_, sy_);
    visited_[sy_][sx_] = true;

    while (!queue.empty())
    {
      auto [x, y] = queue.front();
      queue.pop();

      for (int i = 0; i < 4; i++)
      {
        if (is_valid_(x + dx[i], y + dy[i]) && !visited_[y + dy[i]][x + dx[i]])
        {
          parents_[y + dy[i]][x + dx[i]] = std::make_pair(x, y);
          queue.emplace(x + dx[i], y + dy[i]);
          visited_[y + dy[i]][x + dx[i]] = true;
        }
      }
    }
  }

  auto trace_path(bool &possible) -> std::vector<char>
  {
    std::vector<char> path{};
    int x{dx_}, y{dy_};
    while (x != sx_ || y != sy_)
    {
      auto &[p_x, p_y] = parents_[y][x];
      if (p_x == -1 && p_y == -1)
      {
        possible = false;
        break;
      }
      else
      {
        path.push_back(direction_(p_x, p_y, x, y));
        x = p_x, y = p_y;
      }
    }

    return path;
  }

  auto invert(char c) -> char
  {
    switch (c)
    {
    case 'L':
      return 'R';
    case 'R':
      return 'L';
    case 'U':
      return 'D';
    case 'D':
      return 'U';
    default:
      __builtin_unreachable();
    }
  }
};
