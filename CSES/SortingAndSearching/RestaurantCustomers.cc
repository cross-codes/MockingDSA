#include <algorithm>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 200000;
u32 start[_], end[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  std::cin >> n;

  for (size_t i = 0; i < n; i++)
    std::cin >> start[i] >> end[i];

  std::sort(&::start[0], &::start[n]);
  std::sort(&::end[0], &::end[n]);

  int maxOverlap = 0, currentOverlap = 0;
  size_t ptr1 = 0U, ptr2 = 0U;
  while (true) {
    if (start[ptr1] < end[ptr2]) {
      maxOverlap = std::max(maxOverlap, ++currentOverlap);
      if (++ptr1 == n)
        break;
    } else
      ptr2++, currentOverlap--;
  }

  std::cout << maxOverlap << "\n";

  return 0;
}
