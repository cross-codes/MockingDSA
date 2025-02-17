#include <vector>

class Solution {
public:
  std::vector<int> countBits(int n) {
    std::vector<int> res{};

    for (int i = 0; i <= n; i++) 
      res.push_back(__builtin_popcount(i));

    return res;
  }
};
