#include <cstdint>
#include <iostream>
#include <memory>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 1000001;
constexpr int MOD = static_cast<i64>(1e9 + 7);
std::unique_ptr<u64[]> count(new u64[_]);
u64 coins[100];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  u32 sum;
  std::cin >> n >> sum;

  for (std::size_t i = 0; i < n; i++)
    std::cin >> ::coins[i];

  ::count[0] = 1;
  for (u64 i = 1; i <= sum; i++) {
    for (const u64 &c: coins) {
      if (i >= c)
        ::count[i] += ::count[i - c];
    }
    ::count[i] %= ::MOD;
  }

  std::cout << ::count[sum] << "\n";

  return 0;
}
