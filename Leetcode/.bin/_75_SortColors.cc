#include <vector>

class Solution {
 public:
  void sortColors(std::vector<int> &nums) {
    std::size_t numZero{}, numOne{}, numTwo{};

    for (const int &num : nums) {
      switch (num) {
        case 0:
          numZero++;
          break;
        case 1:
          numOne++;
          break;

        case 2:
          numTwo++;
          break;

        default:
          __builtin_unreachable();
      }
    }

    for (std::size_t i = 0UZ; i < numZero; i++) nums[i] = 0;
    for (std::size_t i = 0UZ; i < numOne; i++) nums[i + numZero] = 1;
    for (std::size_t i = 0UZ; i < numTwo; i++) nums[i + numZero + numOne] = 2;
  }
};
