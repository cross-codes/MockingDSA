#include <algorithm>
#include <cstring>

class Solution {
public:
  int climbStairs(int n) {
    int distinctWays[n + 1];

    std::memset(distinctWays, 0x00, sizeof(distinctWays));

    distinctWays[1] = 1, distinctWays[2] = 2;

    for (int i = 3; i <= n; i++)
      distinctWays[i] = distinctWays[i - 1] + distinctWays[i - 2];

    return distinctWays[n];
  }
};
