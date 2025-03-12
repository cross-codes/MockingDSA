#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<int> plusOne(std::vector<int>& digits) {
    std::size_t n = digits.size();
    std::vector<int> res{};

    int sum   = digits[n - 1] + 1;
    int carry = (sum >= 10) ? 1 : 0;
    res.push_back(sum >= 10 ? sum - 10 : sum);

    for (std::ptrdiff_t i = n - 2; i >= 0; i--) {
      sum   = digits[i] + carry;
      carry = (sum >= 10) ? 1 : 0;
      res.push_back(sum >= 10 ? sum - 10 : sum);
    }

    if (carry > 0)
      res.push_back(carry);

    std::reverse(res.begin(), res.end());
    return res;
  }
};
