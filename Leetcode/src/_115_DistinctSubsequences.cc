#include <climits>
#include <cstdint>
#include <cstring>
#include <string>

class Solution
{
public:
  int numDistinct(std::string s, std::string t)
  {
    int n = static_cast<int>(s.size());
    int m = static_cast<int>(t.size());

    int l[n + 1][m + 1]; // distinct subseq from s[0..i] containing all
                         // of t[0..j];

    int64_t ULIM = static_cast<int64_t>(INT_MAX);
    std::memset(l, 0x00, sizeof(l));

    for (int i = 0; i <= n; i++)
      l[i][0] = 1;

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
      {
        if (s[i - 1] == t[j - 1])
          l[i][j] = static_cast<int>(std::min(
              ULIM, static_cast<int64_t>(l[i - 1][j]) + l[i - 1][j - 1]));
        else
          l[i][j] = l[i - 1][j];
      }

    return l[n][m];
  }
};
