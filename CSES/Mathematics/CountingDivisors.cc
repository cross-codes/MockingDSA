#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 1000000;
u64 divisors[_ + 1];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  for (u32 i = 1; i <= _; i++) {
    for (u32 j = i; j <= _; j += i)
      ::divisors[j]++;
  }

  u32 n;
  std::cin >> n;

  while (n-- > 0) {
    u32 num;
    std::cin >> num;
    std::cout << ::divisors[num] << "\n";
  }

  return 0;
}
