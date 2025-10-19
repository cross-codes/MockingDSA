#include <array>
#include <bitset>
#include <map>
#include <string>

class Solution
{
public:
  long long popcountDepth(long long n, int k)
  {
    if (k == 0)
      return 1;

    int pd[65]{};
    pd[1] = 0;

    for (int i = 2; i < 65; ++i)
      pd[i] = 1 + pd[__builtin_popcount(i)];

    std::string s = std::bitset<64>(n).to_string();
    std::map<std::array<int, 3>, int64_t> lookup{};

    auto call = [&s, &k, &lookup, &pd](auto &&call, int pos, bool equal,
                                       int ones) -> int64_t {
      if (pos == 64)
      {
        if (ones == 0)
          return 0;
        return 1 + pd[ones] == k;
      }

      std::array<int, 3> params = {pos, equal, ones};
      if (lookup.contains(params))
        return lookup[params];

      int64_t res{};
      for (int d = 0; d < 2; ++d)
      {
        if (equal && s[pos] - '0' < d)
          break;

        res +=
            call(call, pos + 1, equal && (d == s[pos] - '0'), ones + (d == 1));
      }

      return lookup[params] = res;
    };

    int64_t count = call(call, 0, true, 0);

    if (k == 1)
      return count - 1;

    return count;
  }
};
