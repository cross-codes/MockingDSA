#include <climits>
#include <cstdint>
#include <utility>

class Solution
{
  auto division(uint32_t x, uint32_t y) -> std::pair<uint32_t, uint32_t>
  {
    if (x == 0)
      return {0, 0};

    auto [q, r] = division(x >> 1, y);
    q <<= 1, r <<= 1;

    if (x & 1)
      r += 1;

    if (r >= y)
    {
      r -= y;
      q += 1;
    }

    return {q, r};
  }

public:
  int divide(int dividend, int divisor)
  {
    if (dividend == 0)
      return 0;

    uint32_t correct_dividend{}, correct_divisor{};
    bool minus1{}, minus2{};

    if (dividend < 0)
    {
      minus1 = true;
      if (dividend == INT_MIN)
        correct_dividend = INT_MAX + 1U;
      else
        correct_dividend = -dividend;
    }
    else
      correct_dividend = dividend;

    if (divisor < 0)
    {
      minus2 = true;
      if (divisor == INT_MIN)
        correct_divisor = INT_MAX + 1U;
      else
        correct_divisor = -divisor;
    }
    else
      correct_divisor = divisor;

    bool minus = minus1 ^ minus2;
    uint32_t q = division(correct_dividend, correct_divisor).first;

    if (minus)
    {
      if (q >= INT_MAX + 1U)
        return INT_MIN;

      return -q;
    }
    else
    {
      if (q > INT_MAX)
        return INT_MAX;

      return q;
    }
  }
};
