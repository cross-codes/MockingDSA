#include <cstdint>
#include <vector>

class Solution
{
public:
  int maxSumAfterPartitioning(std::vector<int> &arr, int k)
  {
    int n = static_cast<int>(arr.size());

    int64_t mxs[n + 1];
    mxs[0] = 0;

    for (int i = 1; i <= n; i++)
    {
      mxs[i] = 0;
      for (int j = 1; j <= std::min(k, i); j++)
      {
        int64_t q = mxs[i - j];
        int64_t mx{};
        for (int l = i - j + 1; l <= i; l++)
          mx = std::max(static_cast<int64_t>(arr[l - 1]), mx);

        mxs[i] = std::max(mxs[i], mx * j + q);
      }
    }

    return static_cast<int>(mxs[n]);
  }
};
