#include <vector>

class Solution {
public:
  int missingNumber(std::vector<int> &nums) {
    int value = 0;
    for (size_t i = 1; i <= nums.size(); i++)
      value ^= i;

    for (size_t i = 0; i < nums.size(); i++)
      value ^= nums[i];

    return value;
  }
};
