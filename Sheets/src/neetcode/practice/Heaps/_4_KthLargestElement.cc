#include <algorithm>
#include <vector>

class Solution {
public:
  int findKthLargest(std::vector<int> &nums, int k) {
    std::sort(nums.begin(), nums.end());
    return nums[nums.size() - k];
  }
};
