#include <algorithm>
#include <numeric>
#include <array>
#include <vector>

class Solution
{
public:
  bool canPartitionKSubsets(std::vector<int> &nums, int k)
  {
    int n = static_cast<int>(nums.size());
    int sum = std::accumulate(nums.begin(), nums.end(), 0) / k;

    std::array<int, 16> subset_sums{};
    std::sort(nums.begin(), nums.end(), std::greater<int>());
    if (nums[0] > sum)
      return false;

    bool possible{};
    auto dfs = [&subset_sums, &possible, &nums, &k, &sum, &n](auto &&dfs, int idx) {
      if (idx == n || possible)
      {
        possible = true;
        return;
      }

      for (int i = 0; i < k; i++)
      {
        if (subset_sums[i] + nums[idx] <= sum)
        {
          subset_sums[i] += nums[idx];
          dfs(dfs, idx + 1);
          subset_sums[i] -= nums[idx];

          if (subset_sums[i] == 0)
            break;
        }
      }
    };

    dfs(dfs, 0);
    return possible;
  }
};
