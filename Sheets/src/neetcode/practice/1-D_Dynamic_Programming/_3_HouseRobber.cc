#include <climits>
#include <cstring>
#include <vector>

class Solution {
public:
  int rob(std::vector<int> &nums) {
    size_t n = nums.size();
    int maxMoney[n];

    std::memset(maxMoney, 0x00, sizeof(maxMoney));

    maxMoney[0] = nums[0], maxMoney[1] = nums[1],
    maxMoney[2] = nums[0] + nums[2];

    for (size_t i = 3; i < n; i++)
      maxMoney[i] = std::max(maxMoney[i - 2], maxMoney[i - 3]) + nums[i];

    return std::max(maxMoney[n - 1], maxMoney[n - 2]);
  }
};
