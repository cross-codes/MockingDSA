#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 1000001;
constexpr int MOD = static_cast<i64>(1e9 + 7);
u64 coins[100], dp[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  u64 sum;
  std::cin >> n >> sum;

  for (size_t i = 0; i < n; i++)
    std::cin >> ::coins[i];

  dp[0] = 1;
  for (size_t j = 0; j < n; j++) {
    for (u64 i = 1; i <= sum; i++) {
      if (i >= coins[j]) {
        dp[i] += dp[i - coins[j]];
        dp[i] %= ::MOD;
      }
    }
  }

  std::cout << dp[sum] << "\n";

  return 0;
}
