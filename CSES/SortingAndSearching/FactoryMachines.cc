#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <functional>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 200000;
i64 times[_];

inline auto monotonicBinarySearch(std::function<i64(i64, size_t)>, i64, i64,
                                  i64, size_t n) -> i64;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  i64 t;
  std::cin >> n >> t;

  i64 minTime = INT64_MAX;
  for (size_t i = 0; i < n; i++) {
    std::cin >> ::times[i];
    minTime = std::min(minTime, ::times[i]);
  }

  std::function<i64(i64, size_t)> totalTimeAt = [](i64 time, size_t n) -> i64 {
    i64 res = 0LL;
    for (size_t i = 0; i < n; i++)
      res += time / ::times[i];

    return res;
  };

  std::cout << monotonicBinarySearch(totalTimeAt, t, 1LL, minTime * t, n)
            << "\n";

  return 0;
}

inline auto monotonicBinarySearch(std::function<i64(i64, size_t)> function,
                                  i64 target, i64 lowerBound, i64 upperBound,
                                  size_t n) -> i64 {
  while (lowerBound < upperBound) {
    i64 mid = (lowerBound + upperBound) >> 1;
    i64 result = function(mid, n);
    if (result < target)
      lowerBound = mid + 1;
    else
      upperBound = mid;
  }

  return lowerBound;
}
