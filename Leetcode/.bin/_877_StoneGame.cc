#include <vector>

class Solution
{
public:
  bool stoneGame(std::vector<int> &piles)
  {
    int n = static_cast<int>(piles.size());

    int advantage[n][n];

    for (int i = 0; i < n; i++)
      advantage[i][i] = piles[i];

    for (int i = n - 1; i >= 0; i--)
      for (int j = i + 1; j < n; j++)
        advantage[i][j] = std::max(piles[i] - advantage[i + 1][j],
                                   piles[j] - advantage[i][j - 1]);

    return advantage[0][n - 1] > 0;
  }
};
