#include <cstdint>
#include <set>
#include <vector>

class Solution
{
public:
  int64_t minimumDifference(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size()) / 3;
    int64_t minsum[3 * n];
    std::fill(minsum, minsum + 3 * n, -1);

    int64_t cur{};
    std::multiset<int> seen{};
    for (int i = 0; i < 3 * n; i++)
    {
      if (static_cast<int>(seen.size()) < n)
      {
        seen.insert(nums[i]);
        cur += nums[i];
        if (static_cast<int>(seen.size()) == n)
          minsum[i] = cur;
      }
      else
      {
        int highest = *(std::prev(seen.end()));
        if (nums[i] < highest)
        {
          seen.erase(std::prev(seen.end()));
          seen.insert(nums[i]);
          cur += nums[i] - highest;
          minsum[i] = cur;
        }
        else
          minsum[i] = cur;
      }
    }

    cur = 0;
    std::multiset<int> rseen{};

    int64_t res{INT64_MAX};
    for (int i = 3 * n - 2; i >= 0; i--)
    {
      if (static_cast<int>(rseen.size()) < n)
      {
        rseen.insert(nums[i + 1]);
        cur += nums[i + 1];
        if (static_cast<int>(rseen.size()) == n && minsum[i] != -1)
          res = std::min(minsum[i] - cur, res);
      }
      else
      {
        int lowest = *rseen.begin();
        if (nums[i + 1] > lowest)
        {
          rseen.erase(rseen.begin());
          rseen.insert(nums[i + 1]);
          cur += nums[i + 1] - lowest;
          if (minsum[i] != -1)
            res = std::min(minsum[i] - cur, res);
        }
        else if (minsum[i] != -1)
          res = std::min(minsum[i] - cur, res);
      }
    }

    return res;
  }
};
