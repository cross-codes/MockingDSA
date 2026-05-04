#include "runner.hh"

namespace Day4
{

auto pt1() -> void
{
  std::vector<std::string> grid{};
  for (std::string s; std::getline(std::cin, s);)
    grid.emplace_back(s);

  int n                      = static_cast<int>(grid.size());
  int m                      = static_cast<int>(grid[0].size());

  const std::string pattern1 = "XMAS";
  const std::string pattern2 = "SAMX";

  auto down                  = [&grid, &n](int y, int x,
                          const std::string_view pattern) -> bool {
    if (y + 3 >= n)
      return false;

    return grid[y][x] == pattern[0] && grid[y + 1][x] == pattern[1] &&
           grid[y + 2][x] == pattern[2] && grid[y + 3][x] == pattern[3];
  };

  auto right = [&grid, &m](int y, int x,
                           const std::string_view pattern) -> bool {
    if (x + 3 >= m)
      return false;

    return grid[y][x] == pattern[0] && grid[y][x + 1] == pattern[1] &&
           grid[y][x + 2] == pattern[2] && grid[y][x + 3] == pattern[3];
  };

  auto drd = [&grid, &n, &m](int y, int x,
                             const std::string_view pattern) -> bool {
    if (y + 3 >= n || x + 3 >= m)
      return false;

    return grid[y][x] == pattern[0] && grid[y + 1][x + 1] == pattern[1] &&
           grid[y + 2][x + 2] == pattern[2] && grid[y + 3][x + 3] == pattern[3];
  };

  auto dld = [&grid, &m](int y, int x, const std::string_view pattern) -> bool {
    if (y - 3 < 0 || x + 3 >= m)
      return false;

    return grid[y][x] == pattern[0] && grid[y - 1][x + 1] == pattern[1] &&
           grid[y - 2][x + 2] == pattern[2] && grid[y - 3][x + 3] == pattern[3];
  };

  int cnt{};
  for (int y = 0; y < n; y++)
    for (int x = 0; x < m; x++)
    {
      cnt += down(y, x, pattern1) + right(y, x, pattern1) +
             drd(y, x, pattern1) + dld(y, x, pattern1);
    }

  for (int y = 0; y < n; y++)
    for (int x = 0; x < m; x++)
    {
      cnt += down(y, x, pattern2) + right(y, x, pattern2) +
             drd(y, x, pattern2) + dld(y, x, pattern2);
    }

  std::cout << cnt << "\n";
}

auto pt2() -> void
{
  std::vector<std::string> grid{};
  for (std::string s; std::getline(std::cin, s);)
    grid.emplace_back(s);

  int n        = static_cast<int>(grid.size());
  int m        = static_cast<int>(grid[0].size());

  auto MAS_SAM = [&grid, &n, &m](int y, int x) -> bool {
    if (y + 2 >= n || x + 2 >= m)
      return false;

    bool cond1 = grid[y][x] == 'M' && grid[y + 1][x + 1] == 'A' &&
                 grid[y + 2][x + 2] == 'S';

    bool cond2 = grid[y][x + 2] == 'S' && grid[y + 1][x + 1] == 'A' &&
                 grid[y + 2][x] == 'M';

    return cond1 && cond2;
  };

  auto MAS_MAS = [&grid, &n, &m](int y, int x) -> bool {
    if (y + 2 >= n || x + 2 >= m)
      return false;

    bool cond1 = grid[y][x] == 'M' && grid[y + 1][x + 1] == 'A' &&
                 grid[y + 2][x + 2] == 'S';

    bool cond2 = grid[y][x + 2] == 'M' && grid[y + 1][x + 1] == 'A' &&
                 grid[y + 2][x] == 'S';

    return cond1 && cond2;
  };

  auto SAM_MAS = [&grid, &n, &m](int y, int x) -> bool {
    if (y + 2 >= n || x + 2 >= m)
      return false;

    bool cond1 = grid[y][x] == 'S' && grid[y + 1][x + 1] == 'A' &&
                 grid[y + 2][x + 2] == 'M';

    bool cond2 = grid[y][x + 2] == 'M' && grid[y + 1][x + 1] == 'A' &&
                 grid[y + 2][x] == 'S';

    return cond1 && cond2;
  };

  auto SAM_SAM = [&grid, &n, &m](int y, int x) -> bool {
    if (y + 2 >= n || x + 2 >= m)
      return false;

    bool cond1 = grid[y][x] == 'S' && grid[y + 1][x + 1] == 'A' &&
                 grid[y + 2][x + 2] == 'M';

    bool cond2 = grid[y][x + 2] == 'S' && grid[y + 1][x + 1] == 'A' &&
                 grid[y + 2][x] == 'M';

    return cond1 && cond2;
  };

  int cnt{};
  for (int y = 0; y < n; y++)
    for (int x = 0; x < m; x++)
      cnt += MAS_MAS(y, x) || MAS_SAM(y, x) || SAM_MAS(y, x) || SAM_SAM(y, x);

  std::cout << cnt << "\n";
}

} // namespace Day4

int main()
{
  Runner::init();
  Runner::exec_all(Day4::pt1, Day4::pt2);
  Runner::end();
  return 0;
}
