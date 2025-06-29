#include <cstdint>
#include <vector>

class Solution
{
public:
  int findPaths(int rows, int cols, int maxMove, int startRow, int startColumn)
  {
    std::vector<std::vector<std::vector<int>>> paths(
        maxMove + 1,
        std::vector<std::vector<int>>(rows, std::vector<int>(cols, -1)));

    constexpr int64_t MOD = static_cast<int64_t>(1e9 + 7);

    auto dfs              = [&rows, &cols, &paths](auto &dfs, int y, int x,
                                      int moves) -> int64_t {
      if (y < 0 || y > rows - 1 || x < 0 || x > cols - 1)
        return 1;

      if (moves == 0)
        return 0;

      if (paths[moves][y][x] != -1)
        return paths[moves][y][x];

      int64_t res{};
      res += dfs(dfs, y - 1, x, moves - 1);
      res += dfs(dfs, y, x - 1, moves - 1);
      res += dfs(dfs, y + 1, x, moves - 1);
      res += dfs(dfs, y, x + 1, moves - 1);

      res %= MOD;
      paths[moves][y][x] = static_cast<int>(res);
      return res;
    };

    return static_cast<int>(dfs(dfs, startRow, startColumn, maxMove));
  }
};
