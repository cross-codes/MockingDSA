#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 1000001;
constexpr int MOD = static_cast<int>(1e9 + 7);

i64 dp[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ::dp[1] = 1, ::dp[2] = 2, ::dp[3] = 4, ::dp[4] = 8, ::dp[5] = 16,
  ::dp[6] = 32;
  for (size_t i = 7; i < _; i++) {
    ::dp[i] = ::dp[i - 1] + ::dp[i - 2] + ::dp[i - 3] + ::dp[i - 4] +
              ::dp[i - 5] + ::dp[i - 6];
    ::dp[i] %= ::MOD;
  }

  size_t n;
  std::cin >> n;
  std::cout << ::dp[n] << "\n";

  return 0;
}
