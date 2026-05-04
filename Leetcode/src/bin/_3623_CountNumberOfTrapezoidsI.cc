#include <cstdint>
#include <unordered_map>
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

    return static_cast<int>(u % m);
  };

public:
  int countTrapezoids(std::vector<std::vector<int>> &points)
  {
    constexpr int64_t MOD = static_cast<int64_t>(1e9 + 7);
    const int64_t MOD2INV = mod_pow(2, MOD - 2, MOD);

    std::unordered_map<int64_t, int64_t> y_map{};
    for (const auto &v : points)
    {
      int y = v[1];
      y_map[y] += 1;
    }

    int64_t tot{};
    for (const auto &[y, e] : y_map)
    {
      tot += (e * (e - 1)) * MOD2INV;
      tot %= MOD;
    }

    int64_t res{};
    for (const auto &[y, e] : y_map)
    {
      int64_t rest = tot - (((e * (e - 1)) * MOD2INV) % MOD);
      res += (((e * (e - 1)) * MOD2INV) % MOD * (rest)) % MOD;
      res %= MOD;
    }

    res *= MOD2INV;
    return static_cast<int>(res % MOD);
  }
};
