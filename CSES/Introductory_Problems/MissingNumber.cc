#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  i64 n;
  std::cin >> n;

  i64 sum = 0LL;
  for (int i = 0; i < n - 1; i++) {
    i64 num;
    std::cin >> num;
    sum += num;
  }

  std::cout << ((n * (n + 1)) >> 1) - sum << "\n";

  return 0;
}
