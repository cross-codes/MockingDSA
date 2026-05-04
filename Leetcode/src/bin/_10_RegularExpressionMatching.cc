#include <cstring>
#include <string>

class Solution
{
public:
  bool isMatch(std::string s, std::string p)
  {
    int n = static_cast<int>(s.size());
    int m = static_cast<int>(p.size());

    // does s[0..i] match p[0..j], 1 indexed
    bool match[n + 1][m + 1];
    std::memset(match, false, sizeof(match));

    match[0][0] = true;
    for (int j = 1; j <= m; j++)
      if (p[j - 1] == '*')
        match[0][j] = match[0][j - 2];

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
      {
        if (p[j - 1] == s[i - 1] || p[j - 1] == '.')
          match[i][j] = match[i - 1][j - 1];
        else
        {
          if (p[j - 1] == '*')
          {
            match[i][j] = match[i][j - 2];
            if (p[j - 2] == s[i - 1] || p[j - 2] == '.')
              match[i][j] = match[i][j - 2] || match[i - 1][j];
          }
        }
      }

    return match[n][m];
  }
};
