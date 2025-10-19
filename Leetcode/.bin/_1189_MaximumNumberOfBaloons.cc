#include <string>

class Solution
{
public:
  int maxNumberOfBalloons(std::string text)
  {
    int b{}, a{}, l{}, o{}, n{};
    bool l_ready{}, o_ready{};
    for (char c : text)
    {
      if (c == 'b')
        b += 1;
      if (c == 'a')
        a += 1;
      if (c == 'l')
      {
        if (l_ready)
        {
          l += 1;
          l_ready = false;
        }
        else
          l_ready = true;
      }
      if (c == 'o')
      {
        {
          if (o_ready)
          {
            o += 1;
            o_ready = false;
          }
          else
            o_ready = true;
        }
      }
      if (c == 'n')
        n += 1;
    }

    return std::min(b, std::min(a, std::min(l, std::min(o, n))));
  }
};
