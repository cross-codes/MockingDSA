#include <climits>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 200000;
i64 a[_], b[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    size_t n;
    std::cin >> n;

    size_t numberToIncrease = 0;
    i64 necessaryDiff = 0;
    i64 minDiffUnecessary = INT64_MAX;

    for (u32 i = 0; i < n; i++)
      std::cin >> a[i];

    for (u32 i = 0; i < n; i++) {
      i64 num;
      std::cin >> num;
      b[i] = num;
      if (b[i] - a[i] > 0) {
        numberToIncrease++;
        necessaryDiff = b[i] - a[i];
      } else {
        minDiffUnecessary = std::min(minDiffUnecessary, a[i] - b[i]);
      }
    }

    if (numberToIncrease > 1)
      std::cout << "NO\n";
    else {
      if (necessaryDiff > minDiffUnecessary)
        std::cout << "NO\n";
      else
        std::cout << "YES\n";
    }
  }

  return 0;
}
