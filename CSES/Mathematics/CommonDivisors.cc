#include <algorithm>
#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 200000;
u64 nums[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  std::cin >> n;

  for (std::size_t i = 0; i < n; i++)
    std::cin >> nums[i];

  u64 maxGCD = 0U;
  for (std::size_t i = 0; i < n; i++)
    for (std::size_t j = i + 1; j < n; j++)
      maxGCD = std::max(maxGCD, std::__gcd(nums[i], nums[j]));

  std::cout << maxGCD << "\n";

  return 0;
}
