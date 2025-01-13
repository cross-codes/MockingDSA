#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cmath>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int q;
  std::cin >> q;

  while (q-- > 0) {
    i64 query;
    i64 n = 1LL, sum = 0LL, prevSum = 0LL, currRange = 9LL;
    std::cin >> query;

    while (query > sum) {
      prevSum = sum;
      sum += n * currRange;
      n++;
      currRange *= 10;
    }

    i64 start = static_cast<i64>(std::pow(10, --n - 1));
    i64 skip = (query - prevSum - 1) / n;
    i64 chSkip = (query - prevSum - 1) % n;

    std::cout << std::to_string(start + skip)[chSkip] << "\n";
  }

  return 0;
}
