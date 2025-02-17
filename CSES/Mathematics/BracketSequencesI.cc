#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>

using usize = std::size_t;
using ssize = std::ptrdiff_t;

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 1000001;
constexpr std::size_t __ = 500002;
constexpr u64 MOD = static_cast<u64>(1e9 + 7);

inline u64 modPow(u64, u64, const u64 &);

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::unique_ptr<u64[]> factorials(new u64[_]), inverseFactorials(new u64[__]);

  factorials[0] = 1;
  for (std::size_t i = 1; i < _; i++)
    factorials[i] = factorials[i - 1] * i % ::MOD;

  for (std::size_t i = 0; i < __; i++)
    inverseFactorials[i] = ::modPow(factorials[i], ::MOD - 2, ::MOD);

  int n;
  std::cin >> n;

  if (n & 1) {
    std::cout << "0\n";
    return 0;
  }

  u32 catalanNumber =
      ((factorials[n] * inverseFactorials[(n >> 1) + 1] % ::MOD) *
       inverseFactorials[n >> 1]) %
      ::MOD;

  std::cout << catalanNumber << "\n";

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
