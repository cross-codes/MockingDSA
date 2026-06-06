#include <vector>

class Solution
{
public:
  int minElement(std::vector<int> &nums)
  {
    auto sum_digits = [](int n) -> int {
      int s{};
      while (n != 0)
      {
        s += n % 10;
        n /= 10;
      }

      return s;
    };

    int mn = INT_MAX;
    for (int e : nums)
      mn = std::min(mn, sum_digits(e));
  }
};
