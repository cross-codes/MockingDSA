#include <climits>
#include <cstring>
#include <memory>
#include <vector>

class Solution {
public:
  int rob(std::vector<int> &nums) {
    size_t n = nums.size();

    if (n <= 3) {
      int maxVal = INT_MIN;
      for (const int &num : nums)
        maxVal = std::max(maxVal, num);

      return maxVal;
    } else {

      std::unique_ptr<int[]> maxMoneyA(new int[n]), maxMoneyB(new int[n]);
      std::memset(maxMoneyA.get(), 0x00, sizeof(int) * n);
      std::memset(maxMoneyB.get(), 0x00, sizeof(int) * n);

      // Do not visit the first house
      maxMoneyA[1] = nums[1], maxMoneyA[2] = nums[2],
      maxMoneyA[3] = nums[1] + nums[3];
      for (size_t i = 4; i < n; i++)
        maxMoneyA[i] = std::max(maxMoneyA[i - 2], maxMoneyA[i - 3]) + nums[i];

      // Do not visit the last house
      maxMoneyB[0] = nums[0], maxMoneyB[1] = nums[1];
      maxMoneyB[2] = nums[0] + nums[2];

      for (size_t i = 3; i < n - 1; i++)
        maxMoneyB[i] = std::max(maxMoneyB[i - 2], maxMoneyB[i - 3]) + nums[i];

      return std::max(std::max(maxMoneyA[n - 1], maxMoneyA[n - 2]),
                      std::max(maxMoneyB[n - 2], maxMoneyB[n - 3]));
    }
  }
};
