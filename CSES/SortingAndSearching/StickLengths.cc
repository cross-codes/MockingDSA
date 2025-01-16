#include <algorithm>
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

constexpr size_t _ = 200000;
int lengths[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  std::cin >> n;

  for (size_t i = 0; i < n; i++)
    std::cin >> ::lengths[i];

  std::sort(&::lengths[0], &::lengths[n]);
  int median = lengths[n >> 1];

  u64 sum = 0U;
  for (size_t i = 0; i < n; i++)
    sum += abs(::lengths[i] - median);

  std::cout << sum << "\n";

  return 0;
}
