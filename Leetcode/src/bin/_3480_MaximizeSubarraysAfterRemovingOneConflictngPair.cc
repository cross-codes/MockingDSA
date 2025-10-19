#include <algorithm>
#include <cstdint>
#include <vector>

class Solution
{
public:
  long long maxSubarrays(int n, std::vector<std::vector<int>> &conflictingPairs)
  {
    std::vector<std::vector<int>> leftendp(n + 1);

    for (const auto &v : conflictingPairs)
    {
      int l = v[0], r = v[1];
      if (l > r)
        std::swap(l, r);
      leftendp[r].push_back(l);
    }

    int64_t ans{};
    std::vector<int64_t> gains(n + 1, 0);

    int mxl{}, smxl{};
    for (int r = 1; r <= n; r++)
    {
      for (int l : leftendp[r])
      {
        if (l > mxl)
        {
          smxl = mxl;
          mxl  = l;
        }
        else if (l > smxl)
        {
          smxl = l;
        }
      }

      ans += r - mxl;
      gains[mxl] += mxl - smxl;
    }

    return ans + *std::max_element(gains.begin(), gains.end());
  }
};
