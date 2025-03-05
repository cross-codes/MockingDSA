#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    std::size_t n = nums.size();
    std::unordered_map<int, size_t> numToIndex{};
    numToIndex.reserve(n);

    for (std::size_t i = 0UZ; i < n; i++) {
      auto it = numToIndex.find(target - nums[i]);
      if (it != numToIndex.end()) [[unlikely]] {
        return {static_cast<int>(i), static_cast<int>(it->second)};
      }
      numToIndex.insert({nums[i], i});
    }

    return {};
  }
};
