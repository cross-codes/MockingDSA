#include <vector>

class Solution
{
public:
  int singleNumber(std::vector<int> &nums)
  {
    int res{};
    for (int e : nums)
      res ^= e;

    return res;
  }
};
