#include <algorithm>
#include <cstring>
#include <vector>

class Solution
{
public:
  int findLongestChain(std::vector<std::vector<int>> &pairs)
  {
    int n           = static_cast<int>(pairs.size());

    auto PAIR_ORDER = [](const std::vector<int> &a,
                         const std::vector<int> &b) -> bool {
      int cmp = a[0] - b[0];
      if (cmp == 0)
        return a[1] < b[1];
      else
        return cmp < 0;
    };

    std::sort(pairs.begin(), pairs.end(), PAIR_ORDER);

    int d[n];
    std::memset(d, 0x00, sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
      int mx{};
      for (int j = 0; j < i; j++)
      {
        if (pairs[j][1] < pairs[i][0])
          mx = std::max(mx, d[j] + 1);
      }

      d[i] = std::max(mx, 1);
    }

    return *std::max_element(d, d + n);
  }
};
