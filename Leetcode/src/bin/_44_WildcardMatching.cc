#include <cstring>
#include <string>

class Solution
{
public:
  bool isMatch(std::string s, std::string p)
  {
    int n = static_cast<int>(s.size()), m = static_cast<int>(p.size());

    // check if s[0..i] matches with p[0..j]
    bool match[n + 1][m + 1];
    std::memset(match, false, sizeof(match));
    match[0][0] = true;

    for (int i = 0; i < m; i++)
      if (p[i] == '*')
        match[0][i + 1] = true;
      else
        break;

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
      {
        if (p[j - 1] == '*')
          match[i][j] = match[i - 1][j] || match[i][j - 1];
        else if (p[j - 1] == '?' || (p[j - 1] == s[i - 1]))
          match[i][j] = match[i - 1][j - 1];
      }

    return match[n][m];
  }
};
