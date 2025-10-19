#include <array>
#include <vector>

class Solution
{
public:
  int findLucky(std::vector<int> &arr)
  {
    std::array<int, 501> freq{};

    for (int e : arr)
      freq[e] += 1;

    for (int i = 500; i > 0; i--)
      if (freq[i] == i)
        return i;

    return -1;
  }
};
