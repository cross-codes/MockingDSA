#include <algorithm>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 200000;
i64 nums[_];

inline auto __JDK__binarySearch(const i64[], int, int, i64) -> int;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    int n;
    std::cin >> n;
    i64 x, y;
    std::cin >> x >> y;

    i64 sum = 0LL;
    for (int i = 0; i < n; i++) {
      i64 num;
      std::cin >> num;
      ::nums[i] = num;
      sum += num;
    }

    std::sort(&::nums[0], &::nums[n]);

    i64 numberOfPairs = 0LL;
    for (int i = 0; i < n; i++) {
      i64 currDiff = sum - ::nums[i];
      i64 lowerBound = currDiff - y, upperBound = currDiff - x;
      int lowerIndex = ::__JDK__binarySearch(::nums, i + 1, n, lowerBound);

      if (lowerIndex < 0)
        lowerIndex = -(lowerIndex + 1);

      if (lowerIndex == n)
        continue;

      i64 refVal = ::nums[lowerIndex];

      for (int j = lowerIndex - 1; j > i; j--) {
        if (::nums[j] == refVal)
          lowerIndex--;
        else
          break;
      }

      int upperIndex = ::__JDK__binarySearch(::nums, i + 1, n, upperBound);
      if (upperIndex < 0) {
        upperIndex = -(upperIndex + 1) - 1;
        if (upperIndex + 1 == lowerIndex)
          continue;
      }

      refVal = ::nums[upperIndex];

      for (int j = upperIndex + 1; j < n; j++) {
        if (::nums[j] == refVal)
          upperIndex++;
        else
          break;
      }

      numberOfPairs += upperIndex - lowerIndex + 1;
    }

    std::cout << numberOfPairs << "\n";
  }

  return 0;
}

inline auto __JDK__binarySearch(const i64 vec[], int fromIndex, int toIndex,
                                i64 key) -> int {

  int low = fromIndex, high = toIndex - 1;
  while (low <= high) {
    int mid = (low + high) >> 1;
    if (vec[mid] < key)
      low = mid + 1;
    else if (vec[mid] > key)
      high = mid - 1;
    else
      return mid;
  }

  return -(low + 1);
}
