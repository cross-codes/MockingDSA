#include <algorithm>
#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 200000;
int lengths[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  std::cin >> n;

  for (std::size_t i = 0; i < n; i++)
    std::cin >> ::lengths[i];

  std::sort(&::lengths[0], &::lengths[n]);
  int median = lengths[n >> 1];

  u64 sum = 0U;
  for (std::size_t i = 0; i < n; i++)
    sum += abs(::lengths[i] - median);

  std::cout << sum << "\n";

  return 0;
}
