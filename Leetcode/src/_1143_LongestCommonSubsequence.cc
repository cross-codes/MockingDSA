#include <array>
#include <string>

class Solution
{
public:
  int longestCommonSubsequence(std::string text1, std::string text2)
  {
    auto m = text1.size(), n = text2.size();
    std::array<std::array<int, 1001>, 1001> d{};

    for (std::size_t i = 1UZ; i < m + 1; i++)
      for (std::size_t j = 1UZ; j < n + 1; j++)
        if (text1[i - 1] == text2[j - 1])
          d[i][j] = d[i - 1][j - 1] + 1;
        else
          d[i][j] = std::max(d[i - 1][j], d[i][j - 1]);

    return d[m][n];
  }
};
