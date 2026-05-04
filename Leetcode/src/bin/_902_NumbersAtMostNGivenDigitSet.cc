#include <array>
#include <cmath>
#include <map>
#include <string>
#include <vector>

class Solution
{
public:
  int atMostNGivenDigitSet(std::vector<std::string> &digits, int n)
  {
    std::string s;
    std::map<std::array<int, 2>, int> lookup;

    auto call = [&s, &lookup, &digits](auto &&call, int i, bool equal) -> int {
      if (i == static_cast<int>(s.size()))
        return 1;

      std::array<int, 2> params = {i, equal};
      if (lookup.contains(params))
        return lookup[params];

      int res{};
      for (std::string dig : digits)
      {
        int d = std::stoi(dig);
        if (equal && d > s[i] - '0')
          break;

        res += call(call, i + 1, equal && (d == s[i] - '0'));
      }

      return lookup[params] = res;
    };

    s       = std::to_string(n);
    int ans = call(call, 0, true);
    for (int l = 1; l < static_cast<int>(s.size()); ++l)
      ans += static_cast<int>(std::pow(digits.size(), l));

    return ans;
  }
};
