#include <algorithm>
#include <climits>
#include <cstdlib>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  long long minCost(std::vector<int> &basket1, std::vector<int> &basket2)
  {
    std::unordered_map<int, int> freq1{}, freq2{};
    int mn{INT_MAX};
    for (int e : basket1)
    {
      freq1[e] += 1;
      mn = std::min(mn, e);
    }

    for (int e : basket2)
    {
      freq2[e] += 1;
      mn = std::min(mn, e);
    }

    std::vector<int> diff{};
    for (auto &[e, f] : freq1)
    {
      int of = freq2[e];
      if ((f + of) & 1)
        return -1;

      else
        for (int i = 0; i < std::abs(f - of) / 2; i++)
          diff.push_back(e);

      freq2.erase(e);
    }

    for (auto &[e, f] : freq2)
    {
      int of = freq1[e];
      if ((f + of) & 1)
        return -1;

      else
        for (int i = 0; i < std::abs(f - of) / 2; i++)
          diff.push_back(e);
    }

    int N = static_cast<int>(diff.size());
    std::sort(diff.begin(), diff.end());

    int64_t cost{};
    for (int i = 0; i < N / 2; i++)
      cost += std::min(diff[i], 2 * mn);

    return cost;
  }
};
