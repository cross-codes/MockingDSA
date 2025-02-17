#include <vector>

class Solution {
public:
  int singleNumber(std::vector<int> &nums) {
    size_t n = nums.size();
    if (n == 1)
      return nums[0];

    int unique = nums[0];
    for (size_t i = 1; i < n; i++)
      unique ^= nums[i];

    return unique;
  }
};
