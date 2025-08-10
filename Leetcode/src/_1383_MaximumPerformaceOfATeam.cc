#include <algorithm>
#include <set>
#include <vector>

class Solution
{
public:
  int maxPerformance(int n, std::vector<int> &speed,
                     std::vector<int> &efficiency, int k)
  {
    constexpr int64_t MOD = static_cast<int64_t>(1e9 + 7);

    std::vector<std::pair<int, int>> stats{};
    for (int i = 0; i < n; i++)
      stats.emplace_back(efficiency[i], speed[i]);

    std::sort(stats.begin(), stats.end(), std::greater<>());

    int64_t mxp{}, sum{}, cnt{};
    std::multiset<int> speeds{};
    for (const auto &[e, s] : stats)
    {
      sum += s;
      cnt += 1;
      speeds.insert(s);
      if (cnt > k)
      {
        sum = sum - *speeds.begin();
        speeds.erase(speeds.begin());
        cnt -= 1;
      }

      mxp = std::max(sum * e, mxp);
    }

    return mxp % MOD;
  }
};
