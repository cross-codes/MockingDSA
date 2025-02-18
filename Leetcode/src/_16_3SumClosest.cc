#include <algorithm>
#include <map>
#include <vector>

class Solution {
public:
  int threeSumClosest(std::vector<int> &nums, int target) {
    std::size_t n = nums.size();
    std::sort(nums.begin(), nums.end());
    std::map<int, bool> sumToSign{};

    for (std::size_t i = 0; i < n; i++) {
      if (i > 0 && nums[i] == nums[i - 1])
        continue;

      for (std::size_t j = i + 1; j < n; j++) {
        for (std::size_t k = j + 1; k < n; k++) {
          int sum = nums[i] + (nums[j] + nums[k]);
          sumToSign[std::abs(sum - target)] = sum >= target;
        }
      }
    }

    auto it = sumToSign.begin();
    return (it->second) ? (it->first) + target : -(it->first) + target;
  }
};
