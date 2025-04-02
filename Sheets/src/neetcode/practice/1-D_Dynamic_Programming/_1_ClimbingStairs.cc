#include <cstring>
#include <memory>

class Solution
{
public:
  int climbStairs(int n)
  {
    std::unique_ptr<int[]> distinctWays(new int[n + 1]);

    std::memset(distinctWays.get(), 0x00, sizeof(int) * n);

    distinctWays[1] = 1, distinctWays[2] = 2;

    for (int i = 3; i <= n; i++)
      distinctWays[i] = distinctWays[i - 1] + distinctWays[i - 2];

    return distinctWays[n];
  }
};
