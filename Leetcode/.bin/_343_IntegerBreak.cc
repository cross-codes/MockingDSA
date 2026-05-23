#include <algorithm>
#include <climits>

class Solution
{
public:
  int integerBreak(int n)
  {
    int mxp[59];
    mxp[1] = 1;
    for (int i = 2; i < 59; i++)
    {
      int mx{INT_MIN};
      for (int j = 1; j < i; j++)
        mx = std::max({mx, j * mxp[i - j], (i - j) * mxp[j],
                       mxp[j] * mxp[i - j], j * (i - j)});

      mxp[i] = mx;
    }

    return mxp[n];
  }
};
