#include <algorithm>
#include <cstring>
#include <vector>

class Solution
{
public:
  bool predictTheWinner(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    // advantage for either player if had to pick from [i..j]
    int advantage[n][n];
    std::memset(advantage, 0x00, sizeof(advantage));

    for (int i = 0; i < n; i++)
      advantage[i][i] = nums[i];

    for (int i = n - 1; i >= 0; i--)
      for (int j = i + 1; j < n; j++)
        advantage[i][j] = std::max(-advantage[i + 1][j] + nums[i],
                                   -advantage[i][j - 1] + nums[j]);

    return advantage[0][n - 1] >= 0;
  }
};
