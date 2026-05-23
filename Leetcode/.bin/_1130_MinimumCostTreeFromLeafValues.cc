#include <climits>
#include <cstring>
#include <vector>

class Solution
{
public:
  int mctFromLeafValues(std::vector<int> &arr)
  {
    int n = static_cast<int>(arr.size());

    int K = std::__lg(n);
    int table[K + 1][n];
    std::memset(table, 0x00, sizeof(table));
    std::copy(arr.begin(), arr.end(), table[0]);

    for (int y = 1; y <= K; y++)
      for (int x = 0, i = (1 << (y - 1)); x <= (n - (1 << y)); x++, i++)
        table[y][x] = std::max(table[y - 1][x], table[y - 1][i]);

    auto query_range = [&table](int L, int R) -> int {
      int i = std::__lg(R - L);
      return std::max(table[i][L], table[i][R - (1 << i)]);
    };

    // mct using the range [i..j] inclusive
    int mct[n][n];
    std::memset(mct, 0x00, sizeof(mct));

    for (int l = 2; l <= n; l++)
      for (int i = 0, j = i + l - 1; j < n; i++, j++)
      {
        mct[i][j] = INT_MAX;
        for (int k = i; k < j; k++)
        {
          int q = mct[i][k] + mct[k + 1][j] +
                  query_range(i, k + 1) * query_range(k + 1, j + 1);
          mct[i][j] = std::min(q, mct[i][j]);
        }
      }

    return mct[0][n - 1];
  }
};
