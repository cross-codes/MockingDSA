#include <cstring>
#include <string>

class Solution
{
public:
  int minDistance(std::string s, std::string t)
  {
    int n = static_cast<int>(s.size());
    int m = static_cast<int>(t.size());

    int e[n + 1][m + 1];
    std::memset(e, 0x00, sizeof e);

    if (n == 0 || m == 0)
      return std::max(n, m);

    for (int x = 0; x <= m; x++)
      e[0][x] = x;

    for (int y = 0; y <= n; y++)
      e[y][0] = y;

    for (int y = 1; y <= n; y++)
      for (int x = 1; x <= m; x++)
      {
        int del = e[y - 1][x] + 1;
        int ins = e[y][x - 1] + 1;
        int rep = e[y - 1][x - 1] + (s[y - 1] != t[x - 1]);
        e[y][x] = std::min({del, ins, rep});
      }

    return e[n][m];
  }
};
