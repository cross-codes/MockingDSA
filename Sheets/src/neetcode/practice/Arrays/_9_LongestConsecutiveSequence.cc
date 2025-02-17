#include <algorithm>
#include <vector>

class Solution {
public:
  int longestConsecutive(std::vector<int> &nums) {
    ptrdiff_t maxLength = 0, left = 0, n = nums.size();
    std::sort(nums.begin(), nums.end());
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());

    bool inSeq = false;
    for (ptrdiff_t i = 1; i < n; i++) {
      if (inSeq) {
        if (nums[i] - nums[i - 1] != 1) {
          maxLength = std::max(maxLength, i - left);
          left = i;
          inSeq = false;
        }
      } else {
        if (nums[i] - nums[i - 1] == 1) {
          inSeq = true;
          continue;
        }
        left = i;
      }
    }

    return static_cast<int>(std::max(maxLength, n - left));
  }
};
