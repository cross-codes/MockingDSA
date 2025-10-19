#include <algorithm>
#include <climits>
#include <numeric>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  int minimumDifference(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size()) >> 1;
    int s = std::accumulate(nums.begin(), nums.end(), 0);
    int x = s >> 1;

    std::vector<int> a(nums.begin(), nums.begin() + n),
        b(nums.begin() + n, nums.end());

    std::unordered_map<int, std::vector<int>> sa{}, sb{};
    for (int i = 0; i < (1 << n); i++)
    {
      int cnt{}, suma{}, sumb{};
      for (int j = 0; j < n; j++)
      {
        if (i & (1 << j))
        {
          cnt += 1;
          suma += a[j];
          sumb += b[j];
        }
      }

      sa[cnt].push_back(suma);
      sb[cnt].push_back(sumb);
    }

    for (auto &[i, vec] : sa)
      std::sort(vec.begin(), vec.end());

    for (auto &[i, vec] : sb)
      std::sort(vec.begin(), vec.end());

    int mnd{INT_MAX};
    for (const auto &[i, vec] : sa)
    {
      for (int e : vec)
      {
        int t       = x - e;
        auto &range = sb[n - i];
        auto it     = std::lower_bound(range.begin(), range.end(), t);
        if (it != range.end())
          mnd = std::min(mnd, std::abs(s - ((e + *it) << 1)));
        if (it != range.begin())
        {
          it  = std::prev(it);
          mnd = std::min(mnd, std::abs(s - ((e + *it) << 1)));
        }
      }
    }

    return mnd;
  }
};
