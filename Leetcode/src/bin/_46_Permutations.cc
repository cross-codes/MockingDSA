#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> permute(std::vector<int> &nums) {
    std::vector<std::vector<int>> res;
    std::ranges::sort(nums);
    do {
      res.push_back(nums);
    } while (std::next_permutation(nums.begin(), nums.end()));

    return res;
  }
};
