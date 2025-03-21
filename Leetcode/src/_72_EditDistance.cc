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

    std::array<std::array<int, 501>, 501> d;
    std::iota(d[0].begin(), d[0].begin() + m + 1, 0);
    for (int i = 0; i <= static_cast<int>(n); i++)
      d[i][0] = i;

    for (std::size_t i = 1UZ; i <= n; i++)
      for (std::size_t j = 1UZ; j <= m; j++)
      {
        int cost = word1[i - 1] == word2[j - 1] ? 0 : 1;
        d[i][j]  = std::min(d[i - 1][j] + 1,
                            std::min(d[i][j - 1] + 1, d[i - 1][j - 1] + cost));
      }

    return d[n][m];
  }
};
