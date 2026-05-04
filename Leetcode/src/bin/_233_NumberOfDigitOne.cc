#include <array>
#include <map>
#include <string>

class Solution
{
public:
  int countDigitOne(int n)
  {
    std::string s = std::to_string(n);

    std::map<std::array<int, 3>, int> lookup{};
    auto call = [&s, &lookup](auto &&call, int i, int ones, bool equal) -> int {
      if (i == static_cast<int>(s.size()))
        return ones;

      std::array<int, 3> params = {i, ones, equal};
      if (lookup.contains(params))
        return lookup[params];

      int res{};
      for (int d = 0; d < 10; d++)
      {
        if (equal && d > s[i] - '0')
          break;

        res += call(call, i + 1, ones + (d == 1), equal && (s[i] - '0' == d));
      }

      return lookup[params] = res;
    };

    return call(call, 0, 0, true);
  }
};
