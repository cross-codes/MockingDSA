#include <cstdint>

class Solution
{
public:
  bool isPowerOfTwo(int64_t n)
  {
    return n > 0 && __builtin_popcountll(n) == 1;
  }
};
