#include <vector>

class Solution {
 public:
  int maxProfit(std::vector<int> &prices) {
    std::ptrdiff_t n = prices.size();

    int maxPrice     = prices[n - 1];
    int bestProfit   = 0;
    for (std::ptrdiff_t i = n - 1; i >= 0; i--) {
      maxPrice   = std::max(maxPrice, prices[i]);
      bestProfit = std::max(bestProfit, maxPrice - prices[i]);
    }

    return bestProfit;
  }
};
