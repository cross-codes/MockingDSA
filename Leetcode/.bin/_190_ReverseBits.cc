#include <array>
#include <cstdint>

class Solution
{
public:
  uint32_t reverseBits(uint32_t n)
  {
    std::array<bool, 32> bitset{};
    for (int i = 0; i < 32; i++)
    {
      if (n & (1U << i))
        bitset[i] = true;
    }

    uint32_t res{};
    for (int i = 31; i >= 0; i--)
    {
      if (bitset[i])
        res |= 1 << (31 - i);
    }

    return res;
  }
};
