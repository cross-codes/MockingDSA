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

  int n;
  std::cin >> n;

  i64 currentSum = 0LL, bestSum = LLONG_MIN;
  for (int i = 0; i < n; i++) {
    i64 num;
    std::cin >> num;
    currentSum = std::max(currentSum + num, num);
    bestSum = std::max(bestSum, currentSum);
  }

  std::cout << bestSum << "\n";

  return 0;
}
