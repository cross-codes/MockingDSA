#include <cstring>
#include <string>

class Solution
{
public:
  int minDistance(std::string word1, std::string word2)
  {
    int n = static_cast<int>(word1.size()), m = static_cast<int>(word2.size());

    int l[n + 1][m + 1];
    std::memset(l, 0x00, sizeof l);

    for (int y = 1; y <= n; y++)
      for (int x = 1; x <= m; x++)
        if (word1[y - 1] == word2[x - 1])
          l[y][x] = l[y - 1][x - 1] + 1;
        else
          l[y][x] = std::max(l[y - 1][x], l[y][x - 1]);

    return std::max(n - l[n][m], 0) + std::max(m - l[n][m], 0);
  }
};
