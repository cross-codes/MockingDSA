#include <cstdint>
#include <string>

class Solution
{
public:
  int myAtoi(std::string s)
  {
    int64_t res   = 0LL;
    bool negative = false, leading_whites_over = false, once_sign = false;
    for (const char &c : s)
    {
      if (c == ' ' && !leading_whites_over) [[unlikely]]
        continue;
      else if ((c == '-' || c == '+') && !once_sign) [[unlikely]]
      {
        if (!leading_whites_over) [[unlikely]]
          leading_whites_over = true;

        once_sign = true;
        negative  = c == '-';
      }
      else if (std::isdigit(c))
      {
        if (!leading_whites_over) [[unlikely]]
          leading_whites_over = true;

        if (!once_sign) [[unlikely]]
          once_sign = true;

        res = (10 * res) + (c - '0');
        if (res > INT32_MAX) [[unlikely]]
          return (negative) ? INT32_MIN : INT32_MAX;
      }
      else
        break;
    }

    return static_cast<int>((negative) ? -res : res);
  }
};
