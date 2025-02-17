#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    i64 a, b;
    std::cin >> a >> b;
    if ((2LL * b - a) >= 0LL && ((2LL * b - a) % 3LL == 0LL) &&
        (2LL * a - b) >= 0LL && ((2LL * a - b) % 3LL == 0LL))
      std::cout << "YES\n";
    else
      std::cout << "NO\n";
  }

  return 0;
}
