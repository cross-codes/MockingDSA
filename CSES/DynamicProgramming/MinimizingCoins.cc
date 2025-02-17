#include <climits>
#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 1000001;
int dp[_];
int coins[100];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  i64 x;
  std::cin >> n >> x;

  for (std::size_t i = 0; i < n; i++)
    std::cin >> ::coins[i];

  for (std::size_t i = 1; i < _; i++) {
    int bestNumber = INT_MAX;
    for (std::size_t j = 0; j < n; j++) {
      int coin = ::coins[j];
      if (coin <= static_cast<int>(i) && ::dp[i - coin] != -1)
        bestNumber = std::min(bestNumber, ::dp[i - coin] + 1);
    }

    if (bestNumber == INT_MAX)
      ::dp[i] = -1;
    else
      ::dp[i] = bestNumber;
  }

  std::cout << ::dp[x] << "\n";

  return 0;
}
