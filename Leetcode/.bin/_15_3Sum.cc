#include <algorithm>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    std::size_t n = nums.size();
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> res{};

    for (std::size_t i = 0; i < n; i++) {
      if (nums[i] > 0)
        break;
      if (i > 0 && nums[i] == nums[i - 1]) [[unlikely]]
        continue;

      std::size_t l = i + 1, r = n - 1;
      while (l < r) {
        int sum = nums[i] + (nums[l] + nums[r]);
        if (sum > 0)
          r--;
        else if (sum < 0)
          l++;
        else {
          res.push_back({nums[i], nums[l], nums[r]});
          l++, r--;

          while (l < r && nums[l] == nums[l - 1])
            l++;
          while (l < r && nums[r] == nums[r + 1])
            r--;
        }
      }
    }

    return res;
  }
};
