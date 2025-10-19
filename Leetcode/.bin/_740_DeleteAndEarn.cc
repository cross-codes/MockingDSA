#include <algorithm>
#include <cstring>
#include <map>
#include <vector>

class Solution
{
public:
  int deleteAndEarn(std::vector<int> &nums)
  {
    std::map<int, int> freq{};
    for (int e : nums)
      freq[e] += 1;

    constexpr int N         = static_cast<int>(1e4 + 1);
    constexpr int ceil_log2 = 32 - __builtin_clz(N - 1);
    int offset              = 1 << ceil_log2;

    int tree[offset << 1];
    std::memset(tree, 0x00, sizeof(int) * (offset << 1));

    auto set_at_index = [&tree, &offset](int index, int value) -> void {
      index += offset;
      tree[index] = value;

      while (index != 1)
      {
        tree[index >> 1] = std::max(tree[index], tree[index ^ 1]);
        index >>= 1;
      }
    };

    auto query_range = [&tree, &offset](int L, int R) -> int {
      L += offset, R += offset;

      int result{};
      while (L < R)
      {
        if (L & 1)
        {
          result = std::max(result, tree[L]);
          L += 1;
        }

        if (R & 1)
        {
          R -= 1;
          result = std::max(result, tree[R]);
        }

        L >>= 1, R >>= 1;
      }

      return result;
    };

    int n = static_cast<int>(freq.size());
    int mx[n];
    std::memset(mx, 0x00, sizeof(int) * n);

    int i{};
    for (const auto &[e, f] : freq)
    {
      int best = query_range(0, e - 1);
      mx[i]    = (f * e) + best;
      set_at_index(e, mx[i]);
      i += 1;
    }

    return *std::max_element(mx, mx + n);
  }
};
