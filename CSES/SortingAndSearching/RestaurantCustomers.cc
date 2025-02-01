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

  int maxOverlap = 0, currentOverlap = 0;

  std::sort(&::start[0], &::start[n]);
  std::sort(&::end[0], &::end[n]);

  size_t startIdx = 0U, endIdx = 0U;
  while (startIdx < n && endIdx < n) {
    if (start[startIdx] < end[endIdx])
      currentOverlap++, startIdx++;
    else
      currentOverlap--, endIdx++;

    maxOverlap = std::max(maxOverlap, currentOverlap);
  }

  std::cout << maxOverlap << "\n";

  return 0;
}
