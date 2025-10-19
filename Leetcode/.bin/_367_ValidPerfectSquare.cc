#include <cstdint>
#include <numeric>

class Solution
{
public:
  bool isPerfectSquare(int num)
  {
    int l{-1}, r{1 << 16};

    auto predicate = [&num](int m) {
      return static_cast<int64_t>(num) < static_cast<int64_t>(m) * m;
    };

    while (r - l > 1)
    {
      int m{std::midpoint(l, r)};
      (predicate(m) ? r : l) = m;
    }

    if (l == -1 || r == 1 << 16)
      return false;
    else
      return l * l == num;
  }
};
