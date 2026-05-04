#include <utility>

class Solution
{
public:
  int minMoves(int sx, int sy, int tx, int ty)
  {
    int cnt{};
    while (tx > sx || ty > sy)
    {
      if (ty > tx)
      {
        std::swap(tx, ty);
        std::swap(sx, sy);
      }
      if (tx == ty)
      {
        if (sx == 0)
          tx = 0;
        else
          ty = 0;
      }
      else if (tx >= (ty << 1))
      {
        if (tx & 1)
          return -1;
        else
          tx >>= 1;
      }
      else
        tx -= ty;

      cnt += 1;
    }

    return tx < sx || ty < sy ? -1 : cnt;
  }
};
