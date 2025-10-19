#include <cstring>

class Solution
{
public:
  int numTrees(int n)
  {
    int C[n + 1];
    std::memset(C, 0x00, sizeof(int) * (n + 1));

    C[0] = 1;
    for (int i = 1; i <= n; i++)
      for (int r = 1; r <= i; r++)
        C[i] += C[r - 1] * C[i - r];

    return C[n];
  }
};
