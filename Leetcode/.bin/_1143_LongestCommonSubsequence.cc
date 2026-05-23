#include <cstring>
#include <string>

class Solution
{
public:
  int longestCommonSubsequence(std::string text1, std::string text2)
  {
    int n = static_cast<int>(text1.size());
    int m = static_cast<int>(text2.size());

    int d[n + 1][m + 1];
    std::memset(d, 0x00, sizeof d);
    for (int y = 1; y <= n; y++)
      for (int x = 1; x <= m; x++)
      {
        if (text1[y - 1] == text2[x - 1])
          d[y][x] = d[y - 1][x - 1] + 1;
        else
          d[y][x] = std::max(d[y - 1][x], d[y][x - 1]);
      }

    return d[n][m];
  }
};
