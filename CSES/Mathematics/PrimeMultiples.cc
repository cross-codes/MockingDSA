#include <bits/stdc++.h>

#pragma GCC target("popcnt")

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _PrimeMultiples {

auto run() -> void {
  u64 n;
  std::cin >> n;

  usize k;
  std::cin >> k;

  std::unique_ptr<u64[]> primes(new u64[k]);
  for (usize i = 0; i < k; i++)
    std::cin >> primes[i];

  u64 res{};
  for (u32 i = 1U; i < (1U << k); i++) {
    u64 term{n}, pos{1LL};
    if (pos & i)
      term /= primes[0];

    for (usize j = 1ULL; j < k; j++) {
      pos <<= 1;
      if (pos & i)
        term /= primes[j];
    }

    if (__builtin_popcountll(i) & 1)
      res += term;
    else
      res -= term;
  }

  std::cout << res << "\n";
}

}  // namespace _PrimeMultiples

int main() {
#ifdef CROSS
  FILE* stream = std::freopen("input.txt", "r", stdin);
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

  while (t-- > 0)
    _PrimeMultiples::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
