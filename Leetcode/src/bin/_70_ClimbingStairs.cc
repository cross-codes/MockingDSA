#include <cstring>

class Solution
{
public:
  int climbStairs(int n)
  {
    if (n == 1)
      return 1;

    int num_ways[n + 1];
    std::memset(num_ways, 0x00, sizeof(int) * (n + 1));

    num_ways[1] = 1, num_ways[2] = 2;
    for (int i = 3; i <= n; i++)
      num_ways[i] = num_ways[i - 1] + num_ways[i - 2];

    return num_ways[n];
  }
};
