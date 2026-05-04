#include <algorithm>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target)
  {
    std::vector<std::vector<int>> res{};
    std::sort(nums.begin(), nums.end());
    int n = static_cast<int>(nums.size());

    for (int i = 0; i < n; i++)
    {
      int64_t a = nums[i];
      for (int j = i + 1; j < n; j++)
      {
        int64_t b = nums[j];
        int l{j + 1}, r{n - 1};
        while (l < r)
        {
          int64_t c{nums[l]}, d{nums[r]};
          if (a + b + c + d < target)
          {
            l += 1;
          }
          else if (a + b + c + d > target)
          {
            r -= 1;
          }
          else
          {
            res.push_back({static_cast<int>(a), static_cast<int>(b),
                           static_cast<int>(c), static_cast<int>(d)});
            l += 1;
            r -= 1;
            while (l < r && nums[l] == nums[l - 1])
            {
              l += 1;
            }
            while (l < r && nums[r] == nums[r + 1])
            {
              r -= 1;
            }
          }
        }
      }
    }

    std::sort(res.begin(), res.end());
    auto last = std::unique(res.begin(), res.end());
    res.erase(last, res.end());
    return res;
  }
};
