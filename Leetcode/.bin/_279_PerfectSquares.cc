#include <array>
#include <climits>

class Solution
{
public:
  int numSquares(int n)
  {
    static std::array<int, 101> squares{};
    if (squares[1] == 0)
      for (int i = 1; i <= 100; i++)
        squares[i] = i * i;

    // w[i] -> min ways of summing to i
    // w[i] = minsq(ways[i - sq] + 1);
    int w[n + 1];

    w[0] = 0;
    for (int i = 1; i <= n; i++)
    {
      w[i] = INT_MAX;
      for (int sq : squares)
        if (i >= sq && w[i - sq] != INT_MAX && w[i - sq] != -1)
          w[i] = std::min(w[i], w[i - sq] + 1);

      if (w[i] == INT_MAX)
        w[i] = -1;
    }

    return (w[n] == -1) ? 0 : w[n];
  }
};
