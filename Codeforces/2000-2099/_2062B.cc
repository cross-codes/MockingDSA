#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <climits>
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
    size_t n;
    std::cin >> n;

    bool bad = false;
    for (size_t i = 0; i < n; i++) {
      int num;
      std::cin >> num;
      if (num <= std::max(static_cast<int>(i),
                          static_cast<int>(n) - static_cast<int>(i) - 1)
                     << 1)
        bad = true;
    }

    if (bad)
      std::cout << "NO\n";
    else
      std::cout << "YES\n";
  }

  return 0;
}
