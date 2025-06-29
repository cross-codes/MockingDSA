#include <algorithm>
#include <vector>

class Solution
{
private:
  auto mod_pow(int x, int n, int m) -> int
  {
    if (n == 0)
      return 1 % m;

    int64_t u = static_cast<int64_t>(mod_pow(x, n >> 1, m));
    u         = (u * u) % m;

    if (n & 1)
      u = (u * x) % m;

    return static_cast<int>(u);
  }

public:
  int numSubseq(std::vector<int> &nums, int target)
  {
    constexpr int64_t MOD = static_cast<int64_t>(1e9 + 7);

    std::ranges::sort(nums);

    auto it  = std::upper_bound(nums.begin(), nums.end(), target >> 1);
    int fpos = static_cast<int>(std::distance(nums.begin(), it));

    int64_t res{};
    for (int l = 0; l < fpos; l++)
    {
      auto next =
          std::upper_bound(nums.begin() + l, nums.end(), target - nums[l]);
      if (next == nums.begin() + l)
        break;

      next    = std::prev(next);
      int r   = static_cast<int>(std::distance(nums.begin(), next));

      int exp = std::max(0, r - l);
      res += mod_pow(2, exp, MOD);
      res %= MOD;
    }

    return static_cast<int>(res);
  }
};
