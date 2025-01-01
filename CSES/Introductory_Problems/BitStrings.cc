#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr i64 MOD = static_cast<i64>(1e9 + 7);

inline i64 modPow(i64 base, i64 exponent, const i64 &modulus) {
  i64 result = 1LL;

  while (exponent > 0LL) {
    if (exponent % 2LL == 1LL)
      result = result * base % modulus;
    exponent >>= 1LL;
    base = (base * base) % modulus;
  }

  return result;
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  i64 n;
  std::cin >> n;

  std::cout << ::modPow(2LL, n, ::MOD) << "\n";

  return 0;
}
