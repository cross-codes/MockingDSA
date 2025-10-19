#include <array>
#include <cstdint>

class Solution
{
public:
  int countGoodArrays(int n, int m, int k)
  {
    if (n == 1)
      return m;

    constexpr int MOD = static_cast<int>(1e9 + 7);
    static bool initialized{};
    static std::array<int, 100000> factorials{}, inverse_factorials{};

    auto mod_pow = [](auto &&mod_pow, int x, int n, int m = MOD) -> int {
      if (n == 0)
        return 1 % m;

      int64_t u = mod_pow(mod_pow, x, n >> 1, m);
      u         = (u * u) % m;

      if (n & 1)
        u = (u * x) % m;

      return static_cast<int>(u);
    };

    if (!initialized)
    {
      factorials[0] = inverse_factorials[0] = 1;
      for (int i = 1; i < 100000; i++)
        factorials[i] = (static_cast<int64_t>(factorials[i - 1]) * i) % MOD;

      for (int i = 1; i < 100000; i++)
        inverse_factorials[i] = mod_pow(mod_pow, factorials[i], MOD - 2);

      initialized = true;
    }

    int64_t coeff =
        ((static_cast<int64_t>(factorials[n - 1]) * inverse_factorials[k]) %
         MOD * inverse_factorials[n - k - 1]) %
        MOD;

    int64_t power = mod_pow(mod_pow, m - 1, n - k - 1);

    return (((m * power) % MOD) * coeff) % MOD;
  }
};
