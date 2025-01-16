#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr u64 MOD = static_cast<u64>(1e9 + 7);
inline u64 modPow(u64, u64, const u64 &);

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  u32 n;
  std::cin >> n;

  while (n-- > 0) {
    u64 a, b, c;
    std::cin >> a >> b >> c;
    std::cout << ::modPow(a, ::modPow(b, c, ::MOD - 1), MOD) << "\n";
  }

  return 0;
}

inline auto modPow(u64 base, u64 exponent, const u64 &modulus = ::MOD) -> u64 {
  u64 res = 1;
  while (exponent > 0) {
    if (exponent & 1)
      res = res * base % modulus;
    exponent >>= 1;
    base = (base * base) % modulus;
  }

  return res;
}
