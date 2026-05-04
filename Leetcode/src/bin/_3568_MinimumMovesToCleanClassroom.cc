#include <cstdint>
#include <cstring>
#include <map>
#include <queue>
#include <string>
#include <vector>

class Solution
{
public:
  int minMoves(std::vector<std::string> &classroom, int energy)
  {
    int n            = static_cast<int>(classroom.size());
    int m            = static_cast<int>(classroom[0].size());

    auto litter_free = [](uint32_t mask) { return mask == 0; };
    auto valid       = [&n, &m](int y, int x) {
      return y >= 0 && y < n && x >= 0 & x < m;
    };

    int cnt{};
    std::map<std::pair<int, int>, int> litter_pos{};
    std::pair<int, int> s{};
    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
      {
        if (classroom[y][x] == 'L')
          litter_pos[{y, x}] = cnt++;
        else if (classroom[y][x] == 'S')
          s = {y, x};
      }

    auto get_lidx = [&litter_pos](int y, int x) -> int {
      return litter_pos[{y, x}];
    };

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};

    int lookup[1 << 11][20][20];
    std::memset(lookup, -1, sizeof lookup);

    // y, x, energy, mask, depth
    std::queue<std::array<int, 5>> queue{};
    std::array<int, 5> params = {s.first, s.second, energy, ((1 << cnt) - 1),
                                 0};
    queue.push(params);
    while (!queue.empty())
    {
      auto [y, x, e, mask, depth] = queue.front();
      queue.pop();

      if (e == 0)
      {
        if (litter_free(mask))
          return depth;
        continue;
      }

      if (e < 0)
        continue;

      if (litter_free(mask))
        return depth;

      if (e <= lookup[mask][y][x])
        continue;
      else
        lookup[mask][y][x] = e;

      for (int i = 0; i < 4; i++)
      {
        int Y{y + dy[i]}, X{x + dx[i]};
        if (valid(Y, X) && classroom[Y][X] != 'X')
        {
          if (classroom[Y][X] == '.' || classroom[Y][X] == 'S')
          {
            std::array<int, 5> nxt = {Y, X, e - 1, mask, depth + 1};
            queue.push(nxt);
          }
          else if (classroom[Y][X] == 'L')
          {
            int lidx = get_lidx(Y, X);
            bool unset{};
            if (mask & (1 << lidx))
            {
              unset = true;
              mask ^= 1 << lidx;
            }

            std::array<int, 5> nxt = {Y, X, e - 1, mask, depth + 1};
            queue.push(nxt);
            if (unset)
              mask |= 1 << lidx;
          }
          else
          {
            std::array<int, 5> nxt = {Y, X, energy, mask, depth + 1};
            queue.push(nxt);
          }
        }
      }
    }

    return -1;
  }
};
