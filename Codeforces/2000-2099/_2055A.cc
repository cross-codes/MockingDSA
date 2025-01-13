#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    int n, a, b;
    std::cin >> n >> a >> b;

    if ((a - b) % 2 == 0)
      std::cout << "YES\n";
    else
      std::cout << "NO\n";
  }

  return 0;
}
