#include <vector>

class Solution {
public:
  std::vector<int> twoSum(std::vector<int> &numbers, int target) {
    std::ptrdiff_t n = numbers.size();
    std::ptrdiff_t l = 0, r = n - 1;

    while (numbers[l] + numbers[r] > target) {
      r--;
    }

    int currentSum = numbers[l] + numbers[r];
    while (l < r) {
      if (currentSum == target)
        return {static_cast<int>(l + 1), static_cast<int>(r + 1)};

      l++;
      while (numbers[l] + numbers[r] > target)
        r--;
      currentSum = numbers[l] + numbers[r];
    }

    return {};
  }
};
