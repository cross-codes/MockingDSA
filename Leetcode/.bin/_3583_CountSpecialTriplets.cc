#include <cstdint>
#include <unordered_map>
#include <vector>

constexpr int MOD = static_cast<int>(1e9 + 7);

class Solution
{
public:
  int specialTriplets(std::vector<int> &nums)
  {
    int n{static_cast<int>(nums.size())};
    std::vector<int> left(n, 0), right(n, 0);
    std::unordered_map<int, int> left_map{}, right_map{};
    for (int i = 0; i < n; i++)
    {
      left[i] = left_map[nums[i] << 1];
      left_map[nums[i]] += 1;
    }

    for (int i = n - 1; i >= 0; i--)
    {
      right[i] = right_map[nums[i] << 1];
      right_map[nums[i]] += 1;
    }

    int64_t res{};
    for (int i = 0; i < n; i++)
    {
      res += (static_cast<int64_t>(left[i]) * right[i]) % MOD;
      res %= MOD;
    }

    return static_cast<int>(res);
  }
};
