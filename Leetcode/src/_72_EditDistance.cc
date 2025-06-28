#include <cstring>
#include <string>

class Solution
{
public:
  int minDistance(std::string x, std::string y)
  {
    int n = static_cast<int>(x.size());
    int m = static_cast<int>(y.size());

    if (n == 0 || m == 0)
      return std::max(n, m);

    int e[n + 1][m + 1]; // min ops to make x[0..i] = y[0..j]
    std::memset(e, 0x00, sizeof(e));

    for (int i = 0; i <= n; i++)
      e[i][0] = i;

    for (int i = 0; i <= m; i++)
      e[0][i] = i;

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
      {
        int del = e[i - 1][j] + 1;
        int add = e[i][j - 1] + 1;
        int rep = e[i - 1][j - 1] + (x[i - 1] != y[j - 1]);

        e[i][j] = std::min(del, std::min(add, rep));
      }

    return e[n][m];
  }
};
