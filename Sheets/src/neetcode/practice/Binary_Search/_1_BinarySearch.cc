#include <vector>

class Solution {
public:
  int search(std::vector<int> &nums, int target) {
    ptrdiff_t i = 0, j = nums.size() - 1;

    while (i <= j) {
      ptrdiff_t m = (i + j) >> 1;
      if (target > nums[m])
        i = m + 1;
      else if (target < nums[m])
        j = m - 1;
      else
        return static_cast<int>(m);
    }

    return -1;
  }
};
