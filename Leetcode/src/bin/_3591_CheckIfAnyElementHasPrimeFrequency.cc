#include <array>
#include <vector>

class Solution
{
public:
  bool checkPrimeFrequency(std::vector<int> &nums)
  {
    std::array<int, 101> freq{};
    for (int e : nums)
      freq[e] += 1;

    auto is_prime = [](int n) -> bool {
      if (n < 2)
        return false;

      int x = 2;
      while (x * x <= n)
      {
        if (n % x == 0)
          return false;
        x = x + 1;
      }

      return true;
    };

    for (int e : freq)
    {
      if (e == 0)
        continue;

      if (is_prime(e))
        return true;
    }

    return false;
  }
};
