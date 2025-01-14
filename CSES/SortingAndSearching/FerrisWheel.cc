#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <algorithm>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 200000;
i64 weights[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  i64 x;
  std::cin >> n >> x;

  for (size_t i = 0; i < n; i++)
    std::cin >> ::weights[i];

  std::sort(&::weights[0], &::weights[n]);

  i64 l = 0, r = n - 1;
  size_t numberOfGondolas = 0;
  while (l <= r) {
    i64 weightLeft = ::weights[l], weightRight = ::weights[r];
    if (weightLeft + weightRight <= x)
      l++, r--;
    else if (weightLeft + weightRight > x)
      r--;

    numberOfGondolas++;
  }

  std::cout << numberOfGondolas << "\n";

  return 0;
}
