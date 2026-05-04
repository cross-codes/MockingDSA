#include <cstdint>
#include <vector>

class Solution
{
public:
  int beautifulSplits(std::vector<int> &nums)
  {
    int n     = static_cast<int>(nums.size());
    int64_t A = static_cast<int64_t>(1e9 - 7),
            B = static_cast<int64_t>(4e8 + 21);

    int64_t p[n + 1], h[n + 1];
    p[0] = 1, h[0] = 0;

    for (int i = 1; i <= n; i++)
    {
      p[i] = (A * p[i - 1]) % B;
      h[i] = (A * h[i - 1] + nums[i - 1]) % B;
    }

    auto get_hash = [&h, &p, &B](int L, int R) -> int64_t {
      int64_t hash = h[R] - h[L] * p[R - L];
      return (hash % B + B) % B;
    };

    auto is_prefix = [&get_hash, &n](int s1, int e1, int s2, int e2) -> bool {
      if (s2 + e1 - s1 > n || e1 - s1 > e2 - s2)
        return false;

      return get_hash(s1, e1) == get_hash(s2, s2 + e1 - s1);
    };

    int cnt{};
    for (int i = 1; i <= n - 2; i++)
      for (int j = i + 1; j <= n - 1; j++)
      {
        // [0..i) ,[i.. j), [j..]
        if (is_prefix(0, i, i, j) || is_prefix(i, j, j, n))
          cnt += 1;
      }

    return cnt;
  }
};
