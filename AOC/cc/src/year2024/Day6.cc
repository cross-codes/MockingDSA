#include "runner.hh"

namespace Day6
{

enum class Direction
{
  UNINITIALIZED,
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

auto pt1() -> void
{
  std::vector<std::string> grid{};
  for (std::string s; std::getline(std::cin, s);)
    grid.push_back(s);

  int n = static_cast<int>(grid.size());
  int m = static_cast<int>(grid[0].size());

  std::array<int, 2> pos{};
  Direction dir{};
  for (int y = 0; y < n; y++)
    for (int x = 0; x < m; x++)
    {
      if (grid[y][x] == '^')
      {
        pos[0] = y, pos[1] = x;
        dir = Direction::UP;
        break;
      }
      else if (grid[y][x] == '>')
      {
        pos[0] = y, pos[1] = x;
        dir = Direction::RIGHT;
        break;
      }
      else if (grid[y][x] == 'v')
      {
        pos[0] = y, pos[1] = x;
        dir = Direction::DOWN;
        break;
      }
      else if (grid[y][x] == '<')
      {
        pos[0] = y, pos[1] = x;
        dir = Direction::LEFT;
        break;
      }
    }

  auto chdir = [](Direction &dir) -> void {
    switch (dir)
    {
    case Direction::UP:
      dir = Direction::RIGHT;
      break;

    case Direction::RIGHT:
      dir = Direction::DOWN;
      break;

    case Direction::DOWN:
      dir = Direction::LEFT;
      break;

    case Direction::LEFT:
      dir = Direction::UP;
      break;

    default:
      std::unreachable();
    }
  };

  auto out_of_bounds = [&n, &m](int y, int x) -> bool {
    return y >= n || x >= m || x < 0 || y < 0;
  };

  bool visited[n][m];
  std::memset(visited, false, sizeof visited);

  int cnt{1};
  visited[pos[0]][pos[1]] = true;

  while (!out_of_bounds(pos[0], pos[1]))
  {
    if (dir == Direction::UP)
    {
      int Y{pos[0] - 1}, X{pos[1]};
      if (!out_of_bounds(Y, X) && grid[Y][X] == '#')
        chdir(dir);
      else
      {
        pos[0] = Y, pos[1] = X;
        if (!out_of_bounds(Y, X) && !visited[Y][X])
        {
          cnt += 1;
          visited[Y][X] = true;
        }
      }
    }
    else if (dir == Direction::RIGHT)
    {
      int Y{pos[0]}, X{pos[1] + 1};
      if (!out_of_bounds(Y, X) && grid[Y][X] == '#')
        chdir(dir);
      else
      {
        pos[0] = Y, pos[1] = X;
        if (!out_of_bounds(Y, X) && !visited[Y][X])
        {
          cnt += 1;
          visited[Y][X] = true;
        }
      }
    }
    else if (dir == Direction::DOWN)
    {
      int Y{pos[0] + 1}, X{pos[1]};
      if (!out_of_bounds(Y, X) && grid[Y][X] == '#')
        chdir(dir);
      else
      {
        pos[0] = Y, pos[1] = X;
        if (!out_of_bounds(Y, X) && !visited[Y][X])
        {
          cnt += 1;
          visited[Y][X] = true;
        }
      }
    }
    else if (dir == Direction::LEFT)
    {
      int Y{pos[0]}, X{pos[1] - 1};
      if (!out_of_bounds(Y, X) && grid[Y][X] == '#')
        chdir(dir);
      else
      {
        pos[0] = Y, pos[1] = X;
        if (!out_of_bounds(Y, X) && !visited[Y][X])
        {
          cnt += 1;
          visited[Y][X] = true;
        }
      }
    }
  }

  std::cout << cnt << "\n";
}

auto pt2() -> void
{
  std::vector<std::string> grid{};
  for (std::string s; std::getline(std::cin, s);)
    grid.push_back(s);

  int n = static_cast<int>(grid.size());
  int m = static_cast<int>(grid[0].size());

  std::array<int, 2> pos{};
  Direction dir{};
  for (int y = 0; y < n; y++)
    for (int x = 0; x < m; x++)
    {
      if (grid[y][x] == '^')
      {
        pos[0] = y, pos[1] = x;
        dir = Direction::UP;
        break;
      }
      else if (grid[y][x] == '>')
      {
        pos[0] = y, pos[1] = x;
        dir = Direction::RIGHT;
        break;
      }
      else if (grid[y][x] == 'v')
      {
        pos[0] = y, pos[1] = x;
        dir = Direction::DOWN;
        break;
      }
      else if (grid[y][x] == '<')
      {
        pos[0] = y, pos[1] = x;
        dir = Direction::LEFT;
        break;
      }
    }

  auto chdir = [](Direction &dir) -> void {
    switch (dir)
    {
    case Direction::UP:
      dir = Direction::RIGHT;
      break;

    case Direction::RIGHT:
      dir = Direction::DOWN;
      break;

    case Direction::DOWN:
      dir = Direction::LEFT;
      break;

    case Direction::LEFT:
      dir = Direction::UP;
      break;

    default:
      std::unreachable();
    }
  };

  auto out_of_bounds = [&n, &m](int y, int x) -> bool {
    return y >= n || x >= m || x < 0 || y < 0;
  };

  auto test_loop = [&]() -> bool {
    Direction visited[n][m];
    std::memset(visited, 0x00, sizeof visited);
    visited[pos[0]][pos[1]] = dir;

    while (!out_of_bounds(pos[0], pos[1]))
    {
      if (dir == Direction::UP)
      {
        int Y{pos[0] - 1}, X{pos[1]};
        if (!out_of_bounds(Y, X) && visited[Y][X] == dir)
          return true;

        if (!out_of_bounds(Y, X) && grid[Y][X] == '#')
          chdir(dir);
        else
        {
          pos[0] = Y, pos[1] = X;
          if (!out_of_bounds(Y, X) && visited[Y][X] != Direction::UNINITIALIZED)
            visited[Y][X] = dir;
        }
      }
      else if (dir == Direction::RIGHT)
      {
        int Y{pos[0]}, X{pos[1] + 1};
        if (!out_of_bounds(Y, X) && visited[Y][X] == dir)
          return true;

        if (!out_of_bounds(Y, X) && grid[Y][X] == '#')
          chdir(dir);
        else
        {
          pos[0] = Y, pos[1] = X;
          if (!out_of_bounds(Y, X) && visited[Y][X] == Direction::UNINITIALIZED)
            visited[Y][X] = dir;
        }
      }
      else if (dir == Direction::DOWN)
      {
        int Y{pos[0] + 1}, X{pos[1]};
        if (!out_of_bounds(Y, X) && visited[Y][X] == dir)
          return true;

        if (!out_of_bounds(Y, X) && grid[Y][X] == '#')
          chdir(dir);
        else
        {
          pos[0] = Y, pos[1] = X;
          if (!out_of_bounds(Y, X) && visited[Y][X] == Direction::UNINITIALIZED)
            visited[Y][X] = dir;
        }
      }
      else if (dir == Direction::LEFT)
      {
        int Y{pos[0]}, X{pos[1] - 1};
        if (!out_of_bounds(Y, X) && visited[Y][X] == dir)
          return true;

        if (!out_of_bounds(Y, X) && grid[Y][X] == '#')
          chdir(dir);
        else
        {
          pos[0] = Y, pos[1] = X;
          if (!out_of_bounds(Y, X) && visited[Y][X] == Direction::UNINITIALIZED)
            visited[Y][X] = dir;
        }
      }
    }

    return false;
  };

  int gcnt{};
  int sy = pos[0], sx = pos[1];
  Direction sdir = dir;

  for (int y = 0; y < n; y++)
    for (int x = 0; x < m; x++)
      if (grid[y][x] == '.')
      {
        pos[0] = sy, pos[1] = sx;
        dir        = sdir;

        grid[y][x] = '#';
        gcnt += test_loop();
        grid[y][x] = '.';
      }

  std::cout << gcnt << "\n";
}

} // namespace Day6

int main()
{
  Runner::init();
  Runner::exec_all(Day6::pt1, Day6::pt2);
  Runner::end();
  return 0;
}
