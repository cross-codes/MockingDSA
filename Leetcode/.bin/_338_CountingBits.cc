#include <vector>

#pragma GCC target("popcnt")

class Solution
{
public:
  std::vector<int> countBits(int n)
  {
    std::vector<int> res{};

    for (unsigned int i = 0U; i <= unsigned(n); i++)
      res.push_back(__builtin_popcount(i));

    return res;
  }
};
