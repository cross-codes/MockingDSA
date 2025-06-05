#include <algorithm>
#include <span>
#include <unordered_set>
#include <vector>

template <> struct std::hash<std::vector<int>>
{
  std::size_t operator()(const std::vector<int> &v) const noexcept
  {
    size_t seed        = 0;
    const size_t prime = 0x9e3779b9;
    for (int x : v)
      seed ^= std::hash<int>{}(x) + prime + (seed << 6) + (seed >> 2);

    return seed;
  }
};

class Solution
{
private:
  std::vector<std::vector<int>> res_{};
  std::unordered_set<std::vector<int>> seen_{};

  void two_sum_(const std::span<int> &range, int64_t target, int num1, int num2)
  {
    int n{static_cast<int>(range.size())};
    int l{}, r{n - 1};
    while (l < r && r < n)
    {
      int64_t sum = range[l] + range[r];
      if (sum == target)
      {
        std::vector<int> result = {num1, num2, range[l], range[r]};
        std::sort(result.begin(), result.end());
        if (!seen_.contains(result))
        {
          res_.push_back({num1, num2, range[l], range[r]});
          seen_.insert(result);
        }
        l += 1;
      }
      else if (sum > target)
        r -= 1;
      else
        l += 1;
    }
  }

public:
  std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target)
  {
    int n{static_cast<int>(nums.size())};
    std::sort(nums.begin(), nums.end());

    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
      {
        int num1 = nums[i];
        int num2 = nums[j];
        int64_t x =
            static_cast<int64_t>(target) - (static_cast<int64_t>(num1) + num2);
        two_sum_(std::span<int>(nums.begin() + j + 1, nums.end()), x, num1,
                 num2);
      }

    return res_;
  }
};
