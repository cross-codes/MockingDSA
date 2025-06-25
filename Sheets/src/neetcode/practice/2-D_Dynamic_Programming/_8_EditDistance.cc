#include <cstring>
#include <string>

class Solution
{
public:
  int minDistance(std::string word1, std::string word2)
  {
    int n = static_cast<int>(word1.size());
    int m = static_cast<int>(word2.size());

    if (n == 0 || m == 0)
      return std::max(n, m);

    int e[n + 1][m + 1];
    std::memset(e, 0x00, sizeof(e));

    for (int i = 0; i <= m; i++)
      e[0][i] = i;

    for (int i = 0; i <= n; i++)
      e[i][0] = i;

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
      {
        int del = e[i - 1][j] + 1;
        int ins = e[i][j - 1] + 1;
        int rep = e[i - 1][j - 1] + (word1[i - 1] != word2[j - 1]);

        e[i][j] = std::min(del, std::min(ins, rep));
      }

    return e[n][m];
  }
};
