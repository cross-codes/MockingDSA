#include <algorithm>
#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 200000;
u32 nums[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  std::cin >> n;

  for (std::size_t i = 0; i < n; i++)
    std::cin >> ::nums[i];

  std::sort(&::nums[0], &::nums[n]);

  u64 res = 1ULL;
  for (u32 num : nums) {
    if (num > res)
      break;
    else
      res += num;
  }

  std::cout << res << "\n";

  return 0;
}
