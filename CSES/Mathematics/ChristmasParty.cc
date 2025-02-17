#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 1000000;
constexpr u64 MOD = static_cast<u64>(1e9 + 7);
u64 derangements[_ + 1];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  u32 n;
  std::cin >> n;

  bool even = true;
  for (std::size_t i = 2; i <= n; i++) {
    if (even)
      derangements[i] = i * derangements[i - 1] + 1;
    else
      derangements[i] = i * derangements[i - 1] - 1;

    derangements[i] %= ::MOD;
    even = !even;
  }

  std::cout << derangements[n] << "\n";

  return 0;
}
