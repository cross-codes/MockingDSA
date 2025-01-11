#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> res{};
  int target;

  void search(int sum, const std::vector<int> &nums, std::vector<int> cur,
              size_t idx...) {
    if (sum == target) {
      this->res.push_back(cur);
      return;
    }

    if (sum > target || idx == nums.size())
      return;

    cur.push_back(nums[idx]);
    search(sum + nums[idx], nums, cur, idx);
    cur.pop_back();
    search(sum, nums, cur, idx + 1);
  }

  std::vector<std::vector<int>> combinationSum(std::vector<int> &nums,
                                               int target) {
    this->target = target;
    search(0, nums, {}, 0);
    return this->res;
  }
};
