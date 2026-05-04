#include <string>

class Solution
{
public:
  int equalSubstring(std::string s, std::string t, int maxCost)
  {
    int n = static_cast<int>(s.size());

    int cc{}, best{}, l{}, r{};
    while (r < n)
    {
      cc += std::abs(s[r] - t[r]);
      while (cc > maxCost && l <= r)
      {
        cc -= std::abs(s[l] - t[l]);
        l += 1;
      }

      best = std::max(best, r - l + 1);
      r += 1;
    }

    return best;
  }
};
