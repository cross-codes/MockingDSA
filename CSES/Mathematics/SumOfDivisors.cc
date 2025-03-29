#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _SumOfDivisors {

constexpr u64 MOD = static_cast<u64>(1e9 + 7);

auto autoRangeAPSum(u64 firstTerm, u64 lastTerm) -> u64 {
  u64 res;
  if ((lastTerm - firstTerm + 1) & 1) {
    res = (lastTerm - firstTerm + 1) % MOD;
    res *= ((firstTerm + lastTerm) >> 1) % MOD;
  } else {
    res = ((lastTerm - firstTerm + 1) >> 1) % MOD;
    res *= (firstTerm + lastTerm) % MOD;
  }

  return res % MOD;
}

auto run() -> void {
  u64 n;
  std::cin >> n;

  u64 i{1ULL}, total{};
  while (i <= n) {
    u64 divisors{n / i};
    u64 rangeEndInclusive{n / divisors};

    total += divisors * autoRangeAPSum(i, rangeEndInclusive);
    total %= MOD;

    i = rangeEndInclusive + 1;
  }

  std::cout << total << "\n";
}

}  // namespace _SumOfDivisors

int main() {
#ifdef ANTUMBRA
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
    _SumOfDivisors::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
