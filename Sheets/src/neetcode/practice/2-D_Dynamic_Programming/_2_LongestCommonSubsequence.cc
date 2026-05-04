#include <cstring>
#include <string>

class Solution
{
public:
  int longestCommonSubsequence(std::string text1, std::string text2)
  {
    int n = static_cast<int>(text1.size());
    int m = static_cast<int>(text2.size());

    int l[n + 1][m + 1];
    for (int i = 0; i <= n; i++)
      std::memset(l[i], 0x00, sizeof(int) * (m + 1));

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        if (text1[i - 1] == text2[j - 1])
          l[i][j] = l[i - 1][j - 1] + 1;
        else
          l[i][j] = std::max(l[i - 1][j], l[i][j - 1]);

    return l[n][m];
  }
};
