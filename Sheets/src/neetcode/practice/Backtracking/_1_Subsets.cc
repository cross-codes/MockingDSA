#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> powerSet{};
  std::vector<int> subset{};

  void search(unsigned int idx, std::vector<int> &nums, std::size_t n) {
    if (idx == n)
      this->powerSet.push_back(this->subset);
    else {
      search(idx + 1, nums, n);
      this->subset.push_back(nums[idx]);
      search(idx + 1, nums, n);
      this->subset.pop_back();
    }
  }

  std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
    search(0, nums, nums.size());
    return this->powerSet;
  }
};
