#include <climits>
#include <cstring>
#include <vector>

class Solution
{
public:
  int minScoreTriangulation(std::vector<int> &values)
  {
    int n = static_cast<int>(values.size());

    // optimal triangulation score using a range
    int mnc[n][n];
    std::memset(mnc, 0x00, sizeof(mnc));

    for (int l = 3; l <= n; l++)
      for (int i = 0, j = i + l - 1; j < n; i++, j++)
      {
        mnc[i][j] = INT_MAX;

        for (int k = i + 1; k < j; k++)
        {
          int q     = mnc[i][k] + mnc[k][j] + values[i] * values[j] * values[k];
          mnc[i][j] = std::min(mnc[i][j], q);
        }
      }

    return mnc[0][n - 1];
  }
};
