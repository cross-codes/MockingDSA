#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _BinomialCoefficients {

constexpr std::size_t N = 1000000;
constexpr u64 MOD       = static_cast<u64>(1e9 + 7);
std::array<u64, N + 1> factorials, inverseFactorials;

inline u64 modPow(u64, u64, const u64 &);

auto run() -> void {
  factorials[0] = 1;
  for (std::size_t i = 1; i <= N; i++)
    factorials[i] = factorials[i - 1] * i % MOD;

  for (std::size_t i = 0; i <= N; i++)
    inverseFactorials[i] = modPow(factorials[i], MOD - 2, MOD);

  u32 n;
  std::cin >> n;

  while (n-- > 0) {
    std::size_t a, b;
    std::cin >> a >> b;

    std::cout << ((factorials[a] * inverseFactorials[b]) % MOD *
                  inverseFactorials[a - b]) %
                     MOD
              << "\n";
  }
}

inline auto modPow(u64 base, u64 exponent, const u64 &modulus = MOD) -> u64 {
  u64 res = 1;
  while (exponent > 0) {
    if (exponent & 1) res = res * base % modulus;
    exponent >>= 1;
    base = (base * base) % modulus;
  }

  return res;
}

}  // namespace _BinomialCoefficients

int main() {
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
#if __cplusplus >= 202302L
    std::println(stderr, "Input file not found");
#else
    std::cerr << "Input file not found\n";
#endif
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t{1};

  while (t-- > 0) _BinomialCoefficients::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
