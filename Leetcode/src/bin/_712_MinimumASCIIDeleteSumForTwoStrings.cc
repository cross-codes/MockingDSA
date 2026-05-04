#include <algorithm>
#include <cstring>
#include <string>

class Solution
{
public:
  int minimumDeleteSum(std::string x, std::string y)
  {
    int n = static_cast<int>(x.size());
    int m = static_cast<int>(y.size());

    int d[n + 1][m + 1];
    std::memset(d, 0x00, sizeof(d));

    for (int i = 1; i <= n; i++)
      d[i][0] = d[i - 1][0] + x[i - 1];

    for (int i = 1; i <= m; i++)
      d[0][i] = d[0][i - 1] + y[i - 1];

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
      {
        if (x[i - 1] == y[j - 1])
          d[i][j] = d[i - 1][j - 1];
        else
          d[i][j] = std::min(d[i - 1][j] + x[i - 1], d[i][j - 1] + y[j - 1]);
      }

    return d[n][m];
  }
};
