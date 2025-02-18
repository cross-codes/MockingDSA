#include <cstdint>

class Solution {
public:
  int hammingWeight(std::uint32_t n) { return __builtin_popcount(n); }
};
