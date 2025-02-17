#include <algorithm>
#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 200000;
u32 start[_], end[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  std::cin >> n;

  for (std::size_t i = 0; i < n; i++)
    std::cin >> start[i] >> end[i];

  int maxOverlap = 0, currentOverlap = 0;

  std::sort(&::start[0], &::start[n]);
  std::sort(&::end[0], &::end[n]);

  std::size_t startIdx = 0U, endIdx = 0U;
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
