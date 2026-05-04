#include <array>
#include <vector>

class Solution
{
public:
  int findDuplicate(std::vector<int> &nums)
  {
    std::array<int, 100001> vals{};
    for (int e : nums)
      vals[e] += 1;

    for (int i = 0; i < 100001; i++)
      if (vals[i] > 1)
        return i;

    __builtin_unreachable();
  }
};
