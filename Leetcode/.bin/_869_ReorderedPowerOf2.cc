#include <algorithm>
#include <string>

#pragma GCC target("popcnt")

class Solution
{
public:
  bool reorderedPowerOf2(int n)
  {
    std::string s{std::to_string(n)};
    std::sort(s.begin(), s.end());
    do
    {
      if (s[0] - '0' != 0)
      {
        if (__builtin_popcount(std::stoi(s)) == 1)
          return true;
      }
    } while (std::next_permutation(s.begin(), s.end()));

    return false;
  }
};
