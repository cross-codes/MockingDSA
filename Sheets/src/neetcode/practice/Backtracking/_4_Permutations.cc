#include <algorithm>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> res{};

  std::vector<std::vector<int>> permute(std::vector<int> &nums) {
    std::sort(nums.begin(), nums.end());

    do {
      res.push_back(nums);
    } while (std::next_permutation(nums.begin(), nums.end()));

    return res;
  }
};
