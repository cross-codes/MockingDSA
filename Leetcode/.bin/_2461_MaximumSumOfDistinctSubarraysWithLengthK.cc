#include <cstdint>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  long long maximumSubarraySum(std::vector<int> &nums, int k)
  {
    int n = static_cast<int>(nums.size());
    int64_t mx{};
    std::unordered_map<int, int> distinct{};

    int64_t prefix[n + 1];
    prefix[0] = 0;
    for (int i = 1; i <= n; i++)
      prefix[i] = prefix[i - 1] + nums[i - 1];

    for (int i = 0; i < k; i++)
      distinct[nums[i]] += 1;

    if (static_cast<int>(distinct.size()) == k)
      mx = std::max(mx, prefix[k] - prefix[0]);

    int win_start{};
    for (int i = k; i < n; i++)
    {
      distinct[nums[win_start]] -= 1;
      if (distinct[nums[win_start]] == 0)
        distinct.erase(nums[win_start]);

      win_start += 1;
      distinct[nums[i]] += 1;
      if (static_cast<int>(distinct.size()) == k)
        mx = std::max(mx, prefix[i + 1] - prefix[win_start]);
    }

    return mx;
  }
};
