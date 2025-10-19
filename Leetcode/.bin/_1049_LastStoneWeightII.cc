#include <climits>
#include <cstdlib>
#include <cstring>
#include <numeric>
#include <vector>

class Solution
{
public:
  int lastStoneWeightII(std::vector<int> &stones)
  {
    int n      = static_cast<int>(stones.size());
    int sum    = std::accumulate(stones.begin(), stones.end(), 0);

    int target = sum >> 1;
    bool f[target + 1];
    std::memset(f, 0x00, sizeof(bool) * (target + 1));

    f[0] = true;
    for (int i = 0; i < n; i++)
      for (int j = target; j >= stones[i]; j--)
        f[j] = f[j] | f[j - stones[i]];

    int mn{INT_MAX};
    for (int i = 0; i <= target; i++)
      if (f[i])
        mn = std::min(mn, std::abs(sum - (i << 1)));

    return mn;
  }
};
