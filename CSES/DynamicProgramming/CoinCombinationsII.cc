#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 1000001;
constexpr int MOD = static_cast<i64>(1e9 + 7);
std::unique_ptr<u64[]> distinct(new u64[_]);
std::vector<u64> coins(100);

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  u64 sum;
  std::cin >> n >> sum;

  for (size_t i = 0; i < n; i++)
    std::cin >> ::coins[i];

  ::distinct[0] = 1;
  for (const u64 &c: ::coins) {
    for (u64 i = 1; i <= sum; i++) {
      if (i >= c) {
        ::distinct[i] += ::distinct[i - c];
        ::distinct[i] %= ::MOD;
      }
    }
  }

  std::cout << ::distinct[sum] << "\n";

  return 0;
}
