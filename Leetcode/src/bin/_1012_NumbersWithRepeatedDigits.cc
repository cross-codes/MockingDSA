#include <array>
#include <cstdint>
#include <map>
#include <string>

class Solution
{
public:
  int numDupDigitsAtMostN(int n)
  {
    std::string s;
    std::map<std::array<uint32_t, 4>, int> lookup{};

    auto contains = [](uint32_t seen, int d) -> bool {
      return seen & (1 << d);
    };

    auto call = [&s, &contains, &lookup](auto &&call, uint32_t i, uint32_t seen,
                                         bool equal, bool empty) -> int {
      if (i == static_cast<uint32_t>(s.size()))
        return 1;

      std::array<uint32_t, 4> params = {i, seen, equal, empty};
      if (lookup.contains(params))
        return lookup[params];

      int res{};
      for (int d = 0; d < 10; d++)
      {
        if (!empty && contains(seen, d))
          continue;

        if (equal && d > s[i] - '0')
          break;

        if (d == 0)
        {
          if (!empty)
            seen |= 1 << d;
        }
        else
          seen |= 1 << d;

        res += call(call, i + 1, seen, equal && (d == s[i] - '0'),
                    empty && (d == 0));

        if (d != 0 || !empty)
          seen ^= 1 << d;
      }

      return lookup[params] = res;
    };

    s = std::to_string(n);
    return n - (call(call, 0U, 0U, true, true) - 1);
  }
};
