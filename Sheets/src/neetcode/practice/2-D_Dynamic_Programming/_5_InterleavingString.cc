#include <cstring>
#include <string>

class Solution
{
public:
  bool isInterleave(std::string s1, std::string s2, std::string s3)
  {
    int m = static_cast<int>(s1.length());
    int n = static_cast<int>(s2.length());
    int N = static_cast<int>(s3.length());

    if (n + m != N)
      return false;

    // s3[0..i + j]  can be created from s1[0..i] and s2[0..j]
    bool possible[n + 1][m + 1];
    std::memset(possible, false, sizeof(possible));
    possible[0][0] = true;

    for (int x = 1; x <= m; x++)
      possible[0][x] = (possible[0][x - 1] && (s3[x - 1] == s1[x - 1]));

    for (int y = 1; y <= n; y++)
      possible[y][0] = (possible[y - 1][0] && (s3[y - 1] == s2[y - 1]));

    for (int y = 1; y <= n; y++)
      for (int x = 1; x <= m; x++)
        possible[y][x] = (possible[y - 1][x] && (s3[y + x - 1] == s2[y - 1])) ||
                         (possible[y][x - 1] && (s3[y + x - 1] == s1[x - 1]));

    return possible[n][m];
  }
};
