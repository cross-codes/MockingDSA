#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    std::unordered_map<int, int> index{};

    for (int i = 0; i < static_cast<int>(nums.size()); i++) {
      int num = nums[i];
      auto it = index.find(target - num);
      if (it != index.end())
        return {it->second, i};
      else
        index.insert({num, i});
    }

    return {};
  }
};
