#include <array>
#include <string>

class Solution
{
public:
  std::string longestPalindrome(std::string s)
  {
    std::ptrdiff_t m = s.length();
    std::array<std::array<bool, 1000>, 1000> p{};

    std::ptrdiff_t maxLength{1}, startIndex{};

    for (std::ptrdiff_t i = 0; i < m; i++)
      p[i][i] = true;

    for (std::ptrdiff_t i = 0; i < m - 1; i++)
      if (s[i] == s[i + 1])
      {
        maxLength   = 2;
        startIndex  = i;
        p[i][i + 1] = true;
      }

    for (std::ptrdiff_t length = 3; length <= m; length++)
    {
      for (std::ptrdiff_t start = 0; start < m - length + 1; ++start)
      {
        std::ptrdiff_t end = start + length - 1;
        if (p[start + 1][end - 1] && s[start] == s[end])
        {
          p[start][end] = true;

          if (length > maxLength)
          {
            maxLength  = length;
            startIndex = start;
          }
        }
      }
    }

    return s.substr(startIndex, maxLength);
  }
};
