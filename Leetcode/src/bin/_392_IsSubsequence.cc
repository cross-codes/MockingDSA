#include <cstring>
#include <string>

class Solution
{
public:
  bool isSubsequence(std::string s, std::string t)
  {
    // possible[i][j] -> get [0..j] of s using [0..i] of t, 1 indexed
    bool possible[t.length() + 1][s.length() + 1];
    std::memset(possible, false, sizeof(possible));

    possible[0][0] = true;
    for (size_t i = 0; i < t.length() + 1; i++)
      possible[i][0] = true;

    for (size_t j = 1; j < s.length() + 1; j++)
      for (size_t i = 1; i < t.length() + 1; i++)
        possible[i][j] = possible[i - 1][j] ||
                         (possible[i - 1][j - 1] && t[i - 1] == s[j - 1]);

    return possible[t.length()][s.length()];
  }
};
