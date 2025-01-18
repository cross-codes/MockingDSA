#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 1000000;
constexpr u64 MOD = static_cast<u64>(1e9 + 7);
u64 factorials[_ + 1], inverseFactorials[_ + 1];

inline u64 modPow(u64, u64, const u64 &);

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ::factorials[0] = 1;
  for (size_t i = 1; i <= _; i++)
    ::factorials[i] = ::factorials[i - 1] * i % MOD;

  for (size_t i = 0; i <= _; i++)
    ::inverseFactorials[i] = ::modPow(factorials[i], ::MOD - 2, ::MOD);

  std::string input;
  std::getline(std::cin, input);

  u32 freq[26];
  std::memset(freq, 0, 26 * sizeof(u32));

  for (char &c : input)
    freq[c - 'a']++;

  u64 res = factorials[input.size()];

  for (int num : freq) {
    res *= inverseFactorials[num];
    res %= MOD;
  }

  std::cout << res % MOD << "\n";

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
