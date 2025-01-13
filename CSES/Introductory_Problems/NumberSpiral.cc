#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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
    u64 y, x, l;
    std::cin >> y >> x;
    l = std::max(y, x) - 1;
    if (l & 1) {
      if (y < x)
        std::cout << l * l + y << "\n";
      else
        std::cout << l * l + 2ULL * l - x + 2ULL << "\n";
    } else {
      if (y < x)
        std::cout << l * l + 2ULL * l - y + 2ULL << "\n";
      else
        std::cout << l * l + x << "\n";
    }
  }

  return 0;
}
