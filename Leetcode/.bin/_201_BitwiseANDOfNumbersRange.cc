#include <cstdint>

class Solution
{
public:
  int rangeBitwiseAnd(int left, int right)
  {
    uint32_t num{};
    for (int i = 31; i >= 0; i--)
    {
      if ((left & (1U << i)) && (right & (1U << i)))
        num |= (1U << i);
      else if (!(!(left & (1U << i)) && !(right & (1U << i))))
        break;
    }

    return static_cast<int>(num);
  }
};
