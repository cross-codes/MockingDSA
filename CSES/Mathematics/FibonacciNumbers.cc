#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr u64 MOD = static_cast<u64>(1e9 + 7);

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  u64 n;
  std::cin >> n;

  if (n == 1ULL)
    std::cout << "1\n";
  else {
    u64 a = 1, b = 0, p = 0, q = 1;
    while (n > 0) {
      if (!(n & 1)) {
        u64 qq = (q * q) % MOD;
        q = ((2 * p * q) % MOD + qq) % MOD;
        p = ((p * p) % MOD + qq) % MOD;
        n /= 2;
      } else {
        u64 aq = (a * q) % MOD;
        a = ((((b * q) % MOD + aq) % MOD) + (a * p) % MOD) % MOD;
        b = ((b * p) % MOD + aq) % MOD;
        n--;
      }
    }
    std::cout << b % MOD << "\n";
  }

  return 0;
}
