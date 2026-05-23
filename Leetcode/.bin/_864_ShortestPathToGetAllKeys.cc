#include <bitset>
#include <cstring>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  int shortestPathAllKeys(std::vector<std::string> &grid)
  {
    int n      = static_cast<int>(grid.size());
    int m      = static_cast<int>(grid[0].size());

    auto valid = [&n, &m](int y, int x) -> bool {
      return y >= 0 && y < n && x >= 0 && x < m;
    };

    std::bitset<26> seen{};
    std::pair<int, int> s{};
    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
      {
        if (grid[y][x] == '@')
          s = std::make_pair(y, x);
        else if (grid[y][x] == '.' || grid[y][x] == '#')
          continue;
        else
          seen.set(std::tolower(grid[y][x]) - 'a');
      }

    int cnt = static_cast<int>(seen.count());

    int visited[30][30][1 << 7];
    std::memset(visited, false, sizeof visited);

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    int pos{};
    std::unordered_map<char, int> key{};
    for (int i = 0; i < 26; i++)
      if (seen[i])
        key[static_cast<char>('a' + i)] = pos++;

    // y, x, keys, depth
    std::queue<std::array<int, 4>> queue{};
    std::array<int, 4> params = {s.first, s.second, (1 << cnt) - 1, 0};
    queue.push(params);

    while (!queue.empty())
    {
      auto [y, x, keys, depth] = queue.front();
      queue.pop();

      if (keys == 0)
        return depth;

      if (visited[y][x][keys])
        continue;

      visited[y][x][keys] = true;
      for (int i = 0; i < 4; i++)
      {
        int Y{y + dy[i]}, X{x + dx[i]};
        if (valid(Y, X))
        {
          if (grid[Y][X] == '.' || grid[Y][X] == '@')
          {
            std::array<int, 4> nxt = {Y, X, keys, depth + 1};
            queue.push(nxt);
          }
          else if (std::islower(grid[Y][X]))
          {
            bool unset{};
            int idx = key[grid[Y][X]];
            if (keys & (1 << idx))
            {
              unset = true;
              keys ^= (1 << idx);
            }

            std::array<int, 4> nxt = {Y, X, keys, depth + 1};
            queue.push(nxt);

            if (unset)
              keys |= (1 << idx);
          }
          else if (grid[Y][X] != '#')
          {
            int idx = key[static_cast<char>(std::tolower(grid[Y][X]))];
            if (!(keys & (1 << idx)))
            {
              std::array<int, 4> nxt = {Y, X, keys, depth + 1};
              queue.push(nxt);
            }
          }
        }
      }
    }

    return -1;
  }
};

int main()
{
  std::vector<std::string> grid = {"@.a..", "###.#", "b.A.B"};
  Solution().shortestPathAllKeys(grid);
}
