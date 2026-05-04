#include <cstring>
#include <memory>
#include <vector>

class Solution {
public:
  std::vector<int> productExceptSelf(std::vector<int> &nums) {
    std::size_t n = nums.size();

    std::unique_ptr<int[]> behind(new int[n]);
    std::unique_ptr<int[]> ahead(new int[n]);

    std::memset(behind.get(), 0x00, sizeof(int) * n);
    std::memset(ahead.get(), 0x00, sizeof(int) * n);

    behind[0] = 1, ahead[n - 1] = 1;
    for (std::size_t i = 1; i < n; i++) {
      behind[i] = behind[i - 1] * nums[i - 1];
      ahead[n - i - 1] = ahead[n - i] * nums[n - i];
    }

    std::vector<int> res{};
    for (std::size_t i = 0; i < n; i++)
      res.push_back(behind[i] * ahead[i]);

    return res;
  }
};
