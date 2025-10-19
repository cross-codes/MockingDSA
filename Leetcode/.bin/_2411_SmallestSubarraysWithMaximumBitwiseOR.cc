#include <numeric>
#include <vector>

class Solution
{
public:
  std::vector<int> smallestSubarrays(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    int K = std::__lg(n);
    int table[K + 1][n];
    std::copy(nums.begin(), nums.end(), table[0]);
    for (int y = 1; y <= K; y++)
      for (int x = 0, i = (1 << (y - 1)); x <= (n - (1 << y)); x++, i++)
        table[y][x] = table[y - 1][x] | table[y - 1][i];

    auto query_range = [&table](int L, int R) -> int {
      int i = std::__lg(R - L);
      return table[i][L] | table[i][R - (1 << i)];
    };

    // OR[st..k) is maximal
    auto pred = [&query_range, &n](int st, int k) -> bool {
      return query_range(st, k) == query_range(st, n);
    };

    std::vector<int> res{};
    for (int i = 0; i < n; i++)
    {
      int L{i}, R{n + 1};
      while (R - L > 1)
      {
        int M                = std::midpoint(L, R);
        (pred(i, M) ? R : L) = M;
      }

      res.push_back(R - i);
    }

    return res;
  }
};
