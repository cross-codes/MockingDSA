#include <algorithm>
#include <climits>
#include <cstdint>
#include <vector>

class Solution
{
public:
  int64_t maximumProduct(std::vector<int> &nums, int m)
  {
    int n{static_cast<int>(nums.size())};
    std::vector<int> max_right(n, INT_MIN), min_right(n, INT_MAX);

    int min_so_far{INT_MAX}, max_so_far{INT_MIN};
    for (int i = n - 1; i >= 0; i--)
    {
      min_so_far   = std::min(min_so_far, nums[i]);
      max_so_far   = std::max(max_so_far, nums[i]);
      min_right[i] = min_so_far;
      max_right[i] = max_so_far;
    }

    int window_start{};
    int64_t max_product{INT64_MIN};
    for (int i = m - 1; i < n; i++)
    {
      max_product = std::max(
          max_product, static_cast<int64_t>(nums[window_start]) * max_right[i]);
      max_product = std::max(
          max_product, static_cast<int64_t>(nums[window_start]) * min_right[i]);

      window_start += 1;
    }

    return max_product;
  }
};
