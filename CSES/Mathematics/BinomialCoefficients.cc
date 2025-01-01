#include <array>
#include <iostream>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

constexpr i64 MOD = static_cast<i64>(1e9 + 7);
constexpr int n_max = static_cast<int>(1e6);

constexpr inline int modPow(int base, int exponent, int mod) {
  i64 result = 1;
  for (i64 i = 1, j = base; i <= exponent; i <<= 1, j = j * j % mod) {
    if ((i & exponent) != 0)
      result = result * j % mod;
  }
  return static_cast<int>(result);
}

constexpr auto computeFactorials() -> std::array<int, n_max + 1> {
  std::array<int, n_max + 1> factorials = {1};
  for (int i = 1; i <= n_max; i++)
    factorials[i] = static_cast<i64>(factorials[i - 1]) * i % MOD;

  return factorials;
}

constexpr auto
computeInverseFactorials(const std::array<int, n_max + 1> &factorials)
    -> std::array<int, n_max + 1> {
  std::array<int, n_max + 1> inverseFactorials = {1};
  for (int i = 1; i <= n_max; i++)
    inverseFactorials[i] = modPow(factorials[i], MOD - 2, MOD);

  return inverseFactorials;
}

constexpr auto factorials = ::computeFactorials();
constexpr auto inverseFactorials = ::computeInverseFactorials(::factorials);

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  return 0;
}
