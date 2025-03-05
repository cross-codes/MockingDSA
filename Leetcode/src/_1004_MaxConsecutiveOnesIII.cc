#include <queue>
#include <vector>

class Solution {
 public:
  int longestOnes(std::vector<int> &nums, int k) {
    std::ptrdiff_t n = nums.size();
    std::ptrdiff_t longestWinSize{};
    std::ptrdiff_t winStart{};

    if (k == 0) {
      bool inWindow{false};
      for (std::ptrdiff_t i = 0Z; i < n; i++) {
        if (inWindow) {
          if (nums[i] == 0) {
            longestWinSize = std::max(longestWinSize, i - winStart);
            inWindow       = false;
          }
        } else {
          if (nums[i] == 1) {
            inWindow = true;
            winStart = i;
          }
        }
      }

      return static_cast<int>(inWindow ? std::max(longestWinSize, n - winStart)
                                       : longestWinSize);
    }

    std::queue<std::size_t> zeroPos{};
    for (std::ptrdiff_t i = 0Z; i < n; i++) {
      if (nums[i] == 0) {
        if (zeroPos.size() == k) {
          longestWinSize = std::max(longestWinSize, i - winStart);
          winStart       = zeroPos.front() + 1;
          zeroPos.pop();
        }
        zeroPos.push(i);
      }
    }

    return static_cast<int>(std::max(longestWinSize, n - winStart));
  }
};
