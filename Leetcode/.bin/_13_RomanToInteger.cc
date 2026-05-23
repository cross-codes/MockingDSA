#include <array>
#include <string>

class Solution
{
public:
  int romanToInt(const std::string &s)
  {
    std::array<int, 26> conv = {0, 0, 100, 500, 0, 0, 0, 0, 1, 0, 0,  50, 1000,
                                0, 0, 0,   0,   0, 0, 0, 0, 5, 0, 10, 0,  0};

    int res{}, n{static_cast<int>(s.size())};

    int i{};
    for (; i < n - 1; i++)
    {
      char c = s[i];
      if (c == 'I')
      {
        char next = s[i + 1];
        if (next == 'V' || next == 'X')
        {
          res += conv[next - 'A'] - conv[c - 'A'];
          i += 1;
        }
        else
          res += conv[c - 'A'];
      }
      else if (c == 'X')
      {
        char next = s[i + 1];
        if (next == 'L' || next == 'C')
        {
          res += conv[next - 'A'] - conv[c - 'A'];
          i += 1;
        }
        else
          res += conv[c - 'A'];
      }
      else if (c == 'C')
      {
        char next = s[i + 1];
        if (next == 'D' || next == 'M')
        {
          res += conv[next - 'A'] - conv[c - 'A'];
          i += 1;
        }
        else
          res += conv[c - 'A'];
      }
      else
        res += conv[c - 'A'];
    }

    if (i == n - 1)
      res += conv[s[i] - 'A'];

    return res;
  }
};
