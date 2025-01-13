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

  i64 n;
  std::cin >> n;
  std::cout << n << " ";

  while (n != 1LL) {
    if (n & 1LL)
      n = 3LL * n + 1LL;
    else
      n >>= 1LL;

    std::cout << n << " ";
  }

  std::cout << "\n";

  return 0;
}
