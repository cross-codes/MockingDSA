#include <algorithm>
#include <cstring>
#include <vector>

class Solution
{
public:
  int maxEnvelopes(std::vector<std::vector<int>> &envelopes)
  {
    constexpr int N         = static_cast<int>(1e5 + 1);
    constexpr int ceil_log2 = (N == 1) ? 1 : 32 - __builtin_clz(N - 1);
    constexpr int offset    = 1 << ceil_log2;

    int tree[offset << 1];
    std::memset(tree, 0x00, sizeof(int) * (offset << 1));

    auto set_at_index = [&tree](int index, int value) -> void {
      index += offset;
      tree[index] = value;
      while (index != 1)
      {
        tree[index >> 1] = std::max(tree[index], tree[index ^ 1]);
        index >>= 1;
      }
    };

    auto query_range = [&tree](int L, int R) -> int {
      L += offset, R += offset;
      int res{};

      while (L < R)
      {
        if (L & 1)
        {
          res = std::max(res, tree[L]);
          L += 1;
        }

        if (R & 1)
        {
          R -= 1;
          res = std::max(res, tree[R]);
        }

        L >>= 1;
        R >>= 1;
      }

      return res;
    };

    auto PAIR_ORDER = [](const std::vector<int> &a,
                         const std::vector<int> &b) -> bool {
      int cmp = a[0] - b[0];
      if (cmp == 0)
        return a[1] > b[1];
      else
        return cmp < 0;
    };

    std::sort(envelopes.begin(), envelopes.end(), PAIR_ORDER);

    int n = static_cast<int>(envelopes.size());

    int d[n];
    std::memset(d, 0x00, sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
      int mx = query_range(0, envelopes[i][1]) + 1;
      d[i]   = mx;
      set_at_index(envelopes[i][1], mx);
    }

    return *std::max_element(d, d + n);
  }
};
