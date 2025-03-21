#include <array>
#include <string>

class Solution
{
public:
  int longestPalindromeSubseq(std::string s)
  {
    std::size_t n{s.size()};

    std::array<std::array<int, 1001>, 1001> l{};
    for (std::size_t i = 1UZ; i <= n; i++)
      for (std::ptrdiff_t j = n; j >= 1; j--)
        if (s[i - 1] == s[j - 1])
          l[i][n - j + 1] = l[i - 1][n - j] + 1;
        else
          l[i][n - j + 1] = std::max(l[i - 1][n - j + 1], l[i][n - j]);

    return l[n][n];
  }
};
