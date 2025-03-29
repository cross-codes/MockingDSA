#include <array>
#include <numeric>
#include <string>

class Solution
{
public:
  int minDistance(std::string word1, std::string word2)
  {
    auto n = word1.size(), m = word2.size();
    if (n == 0UZ || m == 0UZ)
      return static_cast<int>(std::max(n, m));

    std::array<std::array<int, 501>, 501> e;
    std::iota(e[0].begin(), e[0].begin() + m + 1, 0);
    for (int i = 0; i <= static_cast<int>(n); i++)
      e[i][0] = i;

    for (std::size_t i = 1UZ; i <= n; i++)
      for (std::size_t j = 1UZ; j <= m; j++)
      {
        int cost = word1[i - 1] == word2[j - 1] ? 0 : 1;
        e[i][j]  = std::min(e[i - 1][j] + 1,
                            std::min(e[i][j - 1] + 1, e[i - 1][j - 1] + cost));
      }

    return e[n][m];
  }
};
