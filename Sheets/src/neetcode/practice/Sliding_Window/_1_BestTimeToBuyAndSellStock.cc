#include <climits>
#include <vector>

class Solution {
public:
  int maxProfit(std::vector<int> &prices) {
    int minPrice = prices[0];
    std::size_t n = prices.size();

    int maxProfit = INT_MIN;
    for (std::size_t i = 1; i < n; i++) {
      maxProfit = std::max(maxProfit, prices[i] - minPrice);
      minPrice = std::min(minPrice, prices[i]);
    }

    return (maxProfit > 0) ? maxProfit : 0;
  }
};
