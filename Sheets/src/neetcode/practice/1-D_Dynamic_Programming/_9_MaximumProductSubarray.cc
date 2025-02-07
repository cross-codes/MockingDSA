#include <climits>
#include <cstring>
#include <memory>
#include <vector>

class Solution {
public:
  int maxProduct(std::vector<int> &nums) {
    size_t n = nums.size();

    std::unique_ptr<int[]> maxProducts(new int[n]), minProducts(new int[n]);
    std::memset(maxProducts.get(), 0x00, sizeof(int) * n);
    std::memset(minProducts.get(), 0x00, sizeof(int) * n);

    int res = nums[0];
    maxProducts[0] = minProducts[0] = nums[0];
    for (size_t i = 1; i < n; i++) {
      maxProducts[i] = std::max(maxProducts[i - 1] * nums[i], nums[i]);
      maxProducts[i] = std::max(maxProducts[i], minProducts[i - 1] * nums[i]);

      minProducts[i] = std::min(minProducts[i - 1] * nums[i], nums[i]);
      minProducts[i] = std::min(minProducts[i], maxProducts[i - 1] * nums[i]);

      res = std::max(res, maxProducts[i]);
    }

    return res;
  }
};
