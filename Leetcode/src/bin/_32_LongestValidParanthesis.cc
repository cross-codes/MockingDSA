#include <algorithm>
#include <string>

class Solution
{
public:
  int longestValidParentheses(std::string s)
  {
    int n = static_cast<int>(s.size());
    if (n == 0)
      return 0;

    int l[n];
    for (int i = 0; i < n; i++)
    {
      if (i == 0 || s[i] == '(')
        l[i] = 0;
      else
      {
        if (s[i - 1] == '(')
        {
          if (i > 1)
            l[i] = 2 + l[i - 2];
          else
            l[i] = 2;
        }
        else
        {
          // s[i - 1] == ')'
          if (i == 1)
          {
            if (s[i - 1] == '(')
              l[i] = 2;
            else
              l[i] = 0;
          }
          else
          {
            if (s[i - 1] == '(')
            {
              int len = l[i - 2];
              l[i]    = 2 + len;
            }
            else
            {
              int len = l[i - 1];
              if (i - len - 1 >= 0)
              {
                if (s[i - len - 1] == '(')
                {
                  l[i] = len + 2;
                  if (i - len - 1 > 0)
                    l[i] += l[i - len - 2];
                }
                else
                  l[i] = 0;
              }
              else
                l[i] = 0;
            }
          }
        }
      }
    }

    return *std::max_element(l, l + n);
  }
};
