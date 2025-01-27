#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <climits>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 1000001;
int dp[_];
int coins[100];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  i64 x;
  std::cin >> n >> x;

  for (size_t i = 0; i < n; i++)
    std::cin >> ::coins[i];

  for (size_t i = 1; i < _; i++) {
    int bestNumber = INT_MAX;
    for (size_t j = 0; j < n; j++) {
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
