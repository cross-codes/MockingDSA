#include <climits>
#include <cstring>
#include <vector>

class Solution
{
public:
  int maxResult(std::vector<int> &nums, int k)
  {
    auto ceilLog2 = [](int n) -> int {
      return (n == 1) ? 1 : 64 - __builtin_clzll(n - 1);
    };

    int n      = static_cast<int>(nums.size());
    int offset = 1 << ceilLog2(n);
    int tree[offset << 1];
    std::memset(tree, 0x00, sizeof(int) * (offset << 1));

    std::copy(nums.begin(), nums.end(), &tree[offset]);
    int i = offset;
    while (i != 1)
    {
      int j = i;

      while (j < (i << 1))
      {
        tree[j >> 1] = std::max(tree[j], tree[j + 1]);
        j += 2;
      }

      i >>= 1;
    }

    auto set_at_index = [&offset, &tree](int index, int value) -> void {
      index += offset;
      tree[index] = value;
      while (index != 1)
      {
        tree[index >> 1] = std::max(tree[index], tree[index ^ 1]);
        index >>= 1;
      }
    };

    auto query_range = [&offset, &tree](int L, int R) -> int {
      L += offset, R += offset;
      int result = INT_MIN;
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

        L >>= 1;
        R >>= 1;
      }

      return result;
    };

    int max_score[n];
    max_score[n - 1] = nums[n - 1];
    set_at_index(n - 1, max_score[n - 1]);

    for (int j = n - 2; j >= 0; j--)
    {
      max_score[j] = nums[j] + query_range(j + 1, std::min(j + k + 1, n));
      set_at_index(j, max_score[j]);
    }

    return max_score[0];
  }
};
