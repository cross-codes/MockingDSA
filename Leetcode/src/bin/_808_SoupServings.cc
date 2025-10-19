#include <algorithm>
#include <array>
#include <map>

class Solution
{
public:
  double soupServings(int n)
  {
    if (n > 5000)
      return 1.00;

    std::map<std::array<int, 2>, double> lookup{};

    auto call_a = [&lookup](auto &&call_a, int amt1, int amt2) -> double {
      std::array<int, 2> params = {amt1, amt2};

      if (amt2 == 0)
        return lookup[params] = 0.0;

      if (amt1 == 0 && amt2 != 0)
        return lookup[params] = 1.00;

      if (lookup.contains(params))
        return lookup[params];

      double case1 = 0.25 * call_a(call_a, std::max(amt1 - 100, 0), amt2);
      double case2 =
          0.25 * call_a(call_a, std::max(amt1 - 75, 0), std::max(amt2 - 25, 0));
      double case3 =
          0.25 * call_a(call_a, std::max(amt1 - 50, 0), std::max(amt2 - 50, 0));
      double case4 =
          0.25 * call_a(call_a, std::max(amt1 - 25, 0), std::max(amt2 - 75, 0));

      return lookup[params] = case1 + case2 + case3 + case4;
    };

    std::map<std::array<int, 2>, double> nxt_lookup{};

    auto call_both = [&nxt_lookup](auto &&call_both, int amt1,
                                   int amt2) -> double {
      std::array<int, 2> params = {amt1, amt2};
      if (amt1 == 0 && amt2 != 0)
        return nxt_lookup[params] = 0.0;

      if (amt2 == 0 && amt1 != 0)
        return nxt_lookup[params] = 0.0;

      if (amt1 == 0 && amt2 == 0)
        return nxt_lookup[params] = 1.00;

      if (nxt_lookup.contains(params))
        return nxt_lookup[params];

      double case1 = 0.25 * call_both(call_both, std::max(amt1 - 100, 0), amt2);
      double case2 = 0.25 * call_both(call_both, std::max(amt1 - 75, 0),
                                      std::max(amt2 - 25, 0));
      double case3 = 0.25 * call_both(call_both, std::max(amt1 - 50, 0),
                                      std::max(amt2 - 50, 0));
      double case4 = 0.25 * call_both(call_both, std::max(amt1 - 25, 0),
                                      std::max(amt2 - 75, 0));

      return nxt_lookup[params] = case1 + case2 + case3 + case4;
    };

    return call_a(call_a, n, n) + 0.5 * call_both(call_both, n, n);
  }
};
