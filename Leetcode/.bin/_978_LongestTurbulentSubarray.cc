#include <cstdlib>
#include <vector>

class Solution
{
public:
  int maxTurbulenceSize(std::vector<int> &arr)
  {
    int n = static_cast<int>(arr.size());
    int res{};

    for (int i = 0, cnt = 0; i + 1 < n; i++, cnt *= -1)
    {
      if (arr[i] > arr[i + 1])
        cnt = cnt > 0 ? cnt + 1 : 1;
      else if (arr[i] < arr[i + 1])
        cnt = cnt < 0 ? cnt - 1 : -1;
      else
        cnt = 0;

      res = std::max(res, std::abs(cnt));
    }

    return res + 1;
  }
};
