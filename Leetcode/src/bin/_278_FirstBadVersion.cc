#include <cstdint>
#include <numeric>

bool isBadVersion(int);

class Solution
{
public:
  int firstBadVersion(int n)
  {
    int64_t l{}, r{static_cast<int64_t>(n) + 1};
    while (r - l > 1)
    {
      int64_t m{std::midpoint(l, r)};
      (isBadVersion(static_cast<int>(m)) ? r : l) = m;
    }

    return static_cast<int>(r);
  }
};
