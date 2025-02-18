#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    std::unordered_map<int, int> numToIndex{};

    std::size_t n = nums.size();
    for (unsigned int i = 0; i < n; i++) {
      int num = nums[i];
      auto it = numToIndex.find(target - num);
      if (it != numToIndex.end()) [[unlikely]] {
        return {it->second, static_cast<int>(i)};
      } else
        numToIndex[num] = i;
    }

    return {};
  }
};
