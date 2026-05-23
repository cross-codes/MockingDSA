#include <vector>

class Solution
{
public:
  int maxBalancedShipments(std::vector<int> &weight)
  {
    int n = static_cast<int>(weight.size());

    int l{}, r{1}, cnt{}, mxwin{weight[0]};
    while (r < n)
    {
      if (weight[r] >= mxwin)
        mxwin = weight[r];
      else
      {
        cnt += 1;
        l = r + 1;
        if (l < n)
          mxwin = weight[l];
      }
      r += 1;
    }

    return cnt;
  }
};
