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

  u64 n;
  std::cin >> n;

  for (u64 i = 1; i <= n; i++) {
    std::cout << (i * i) * (i * i - 1ULL) / 2ULL -
                     4ULL * (i - 1ULL) * (i - 2ULL)
              << "\n";
  }

  return 0;
}
