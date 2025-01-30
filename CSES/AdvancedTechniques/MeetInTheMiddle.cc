#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_map>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 40;
u64 list[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  u64 x;
  std::cin >> n >> x;

  for (size_t i = 0; i < n; i++)
    std::cin >> ::list[i];

  std::sort(&::list[0], &::list[n]);

  std::unordered_map<u64, size_t> firstSums{};
  firstSums.reserve(1 << (n >> 1));

  for (int i = 0; i < (1 << (n >> 1)); i++) {
    u64 currentSum = 0U;
    for (u32 j = 0; j < (n >> 1); j++) {
      if (i & (1 << j))
        currentSum += ::list[j];
      if (currentSum > x)
        break;
    }
    if (currentSum <= x)
      firstSums[currentSum]++;
  }

  u64 cnt = 0U;
  for (int i = 0; i < (1 << (n - (n >> 1))); i++) {
    u64 currentSum = 0U;
    for (u32 j = 0; j < (n - (n >> 1)); j++) {
      if (i & (1 << j))
        currentSum += ::list[j + (n >> 1)];
      if (currentSum > x)
        break;
    }
    if (currentSum <= x)
      cnt += firstSums[x - currentSum];
  }

  std::cout << cnt << "\n";

  return 0;
}
