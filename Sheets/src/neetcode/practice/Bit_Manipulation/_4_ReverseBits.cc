#include <cstdint>

class Solution
{
public:
  uint32_t reverseBits(uint32_t n)
  {
    uint32_t forward = 1 << 31, updater = 1;
    uint32_t res{};

    for (int i = 0; i < 32; i++)
    {
      if (forward & n)
        res |= updater;

      updater <<= 1;
      forward >>= 1;
    }

    return res;
  }
};
