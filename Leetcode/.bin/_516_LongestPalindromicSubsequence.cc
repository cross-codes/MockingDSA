#include <algorithm>
#include <cstring>
#include <string>

class Solution
{
public:
  int longestPalindromeSubseq(std::string s)
  {
    std::string s_cpy = s;
    std::reverse(s_cpy.begin(), s_cpy.end());
    int n = static_cast<int>(s.size());

    int l[n + 1][n + 1];
    std::memset(l, 0x00, sizeof l);
    for (int y = 1; y <= n; y++)
      for (int x = 1; x <= n; x++)
      {
        if (s[y - 1] == s_cpy[x - 1])
          l[y][x] = l[y - 1][x - 1] + 1;
        else
          l[y][x] = std::max(l[y - 1][x], l[y][x - 1]);
      }

    return l[n][n];
  }
};
