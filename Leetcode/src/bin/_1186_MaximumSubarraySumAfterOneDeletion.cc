#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>

class Solution
{
public:
  int maximumSum(std::vector<int> &arr)
  {
    int n = static_cast<int>(arr.size());

    // mx sum using [0..i] and j deletions
    int mx[n + 1][2];
    std::memset(mx, 0xcf, sizeof mx);
    mx[0][0] = 0;

    int res{INT_MIN};
    for (int i = 0; i < 2; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if (i == 0)
          mx[j][i] = std::max(arr[j - 1], mx[j - 1][i] + arr[j - 1]);
        else
          mx[j][i] = std::max(mx[j - 1][i - 1], mx[j - 1][i] + arr[j - 1]);
        res = std::max(res, mx[j][i]);
      }
    }

    return res == 0 ? *std::max_element(arr.begin(), arr.end()) : res;
  }
};
