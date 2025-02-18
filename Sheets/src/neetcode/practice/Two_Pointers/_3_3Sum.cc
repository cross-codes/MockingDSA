#include <algorithm>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    std::vector<std::vector<int>> res{};

    std::sort(nums.begin(), nums.end());
    std::size_t n = nums.size();

    for (std::size_t i = 0; i < n; i++) {
      int aux = nums[i];

      std::ptrdiff_t l = i + 1, r = n - 1;
      while (nums[l] + nums[r] > -aux)
        r--;

      int currentSum = nums[l] + nums[r];
      while (l < r) {
        int left = nums[l], right = nums[r];
        if (currentSum == -aux)
          res.push_back(
              {static_cast<int>(nums[l]), static_cast<int>(nums[r]), aux});

        while (nums[l] == left)
          l++;

        while (nums[l] + nums[r] > -aux)
          r--;

        currentSum = nums[l] + nums[r];
      }

      while (nums[i] == aux)
        i++;
      i--;
    }

    return res;
  }
};
