#include <vector>

class Solution {
 public:
  std::vector<int> rearrangeArray(std::vector<int> &nums) {
    std::size_t n{nums.size()};
    std::vector<int> posSeq{}, negSeq{};

    for (std::size_t i = 0; i < n; i++) {
      if (nums[i] > 0)
        posSeq.push_back(nums[i]);
      else
        negSeq.push_back(nums[i]);
    }

    bool positive{true};
    std::size_t counter{};
    for (std::size_t i = 0UZ; i < n; i++) {
      if (positive)
        nums[i] = posSeq[counter];
      else
        nums[i] = negSeq[counter++];
      positive = !positive;
    }

    return nums;
  }
};
