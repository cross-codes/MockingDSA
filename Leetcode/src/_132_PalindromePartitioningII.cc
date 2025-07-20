#include <cstring>
#include <string>

class Solution
{
public:
  int minCut(std::string s)
  {
    int n = static_cast<int>(s.length());
    bool is_palindrome[n][n];
    std::memset(is_palindrome, false, sizeof is_palindrome);

    for (int i = 0; i < n; i++)
      is_palindrome[i][i] = true;

    for (int i = 0; i < n - 1; i++)
      if (s[i] == s[i + 1])
        is_palindrome[i][i + 1] = true;

    for (int len = 3; len <= n; len++)
      for (int i = 0; i + len <= n; i++)
      {
        int j = i + len - 1;
        if (s[i] == s[j] && is_palindrome[i + 1][j - 1])
          is_palindrome[i][j] = true;
      }

    int mxc[n];
    for (int i = 0; i < n; i++)
      mxc[i] = i;

    for (int i = 0; i < n; i++)
    {
      if (is_palindrome[0][i])
        mxc[i] = 0;
      else
        for (int j = 0; j < i; j++)
        {
          if (is_palindrome[j + 1][i])
            mxc[i] = std::min(mxc[i], mxc[j] + 1);
        }
    }

    return mxc[n - 1];
  }
};
