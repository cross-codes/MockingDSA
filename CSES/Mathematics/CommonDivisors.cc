#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <algorithm>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 200000;
u64 nums[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  std::cin >> n;

  for (size_t i = 0; i < n; i++)
    std::cin >> nums[i];

  u64 maxGCD = 0U;
  for (size_t i = 0; i < n; i++)
    for (size_t j = i + 1; j < n; j++)
      maxGCD = std::max(maxGCD, std::__gcd(nums[i], nums[j]));

  std::cout << maxGCD << "\n";

  return 0;
}
