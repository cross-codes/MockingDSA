#include <algorithm>
#include <cstdint>
#include <string>

class Solution
{
public:
  int longestSubsequence(std::string s, int k)
  {
    int n = static_cast<int>(s.size());
    if (k == 1)
    {
      std::string unset = s.substr(0, n - 1);
      return static_cast<int>(1 + std::count(unset.begin(), unset.end(), '0'));
    }

    uint32_t K = static_cast<uint32_t>(k);
    int ls = std::max(0, 31 - __builtin_clz(K));

    if (ls > n)
      return n;

    std::string unset = s.substr(n - ls, ls);

    K &= ~(1 << ls);
    bool can_add_one{};
    if (K >= std::stoul(unset, nullptr, 2))
      can_add_one = true;

    int res{ls};
    for (int i = n - ls - 1; i >= 0; i--)
      if (can_add_one)
      {
        can_add_one = false;
        res += 1;
      }
      else
        res += (s[i] == '0');

    return res;
  }
};
