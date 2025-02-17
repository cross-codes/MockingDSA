#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  int res = 0;
  for (int i = 0; i < n - 1; i++) {
    int num;
    std::cin >> num;
    res ^= num ^ (i + 1);
  }

  std::cout << (res ^ n) << "\n";

  return 0;
}
