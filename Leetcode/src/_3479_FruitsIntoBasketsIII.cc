#include <cmath>
#include <vector>

class Solution
{
public:
  int numOfUnplacedFruits(std::vector<int> &fruits, std::vector<int> &baskets)
  {
    int n = static_cast<int>(fruits.size()), m = static_cast<int>(std::sqrt(n));

    int blk = (n + m - 1) / m, cnt{};

    std::vector<int> mxb(blk);
    for (int i = 0; i < n; i++)
      mxb[i / m] = std::max(mxb[i / m], baskets[i]);

    for (int e : fruits)
    {
      int j{}, unplaced{1};
      for (j = 0; j < blk; j++)
      {
        if (mxb[j] < e)
          continue;

        int check{};
        mxb[j] = 0;
        for (int i = 0; i < m; i++)
        {
          int pos = (j * m) + i;
          if (pos < n && baskets[pos] >= e && !check)
          {
            baskets[pos] = 0;
            check        = 1;
          }

          if (pos < n)
            mxb[j] = std::max(mxb[j], baskets[pos]);
        }
        unplaced = 0;
        break;
      }

      cnt += unplaced;
    }

    return cnt;
  }
};
