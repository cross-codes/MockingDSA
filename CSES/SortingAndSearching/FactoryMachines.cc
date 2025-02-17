#include <cstdint>
#include <functional>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 200000;
i64 times[_];

inline auto monotonicBinarySearch(std::function<i64(i64, std::size_t)>, i64, i64,
                                  i64, std::size_t n) -> i64;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  i64 t;
  std::cin >> n >> t;

  i64 minTime = INT64_MAX;
  for (std::size_t i = 0; i < n; i++) {
    std::cin >> ::times[i];
    minTime = std::min(minTime, ::times[i]);
  }

  std::function<i64(i64, std::size_t)> totalTimeAt = [](i64 time, std::size_t n) -> i64 {
    i64 res = 0LL;
    for (std::size_t i = 0; i < n; i++)
      res += time / ::times[i];

    return res;
  };

  std::cout << monotonicBinarySearch(totalTimeAt, t, 1LL, minTime * t, n)
            << "\n";

  return 0;
}

inline auto monotonicBinarySearch(std::function<i64(i64, std::size_t)> function,
                                  i64 target, i64 lowerBound, i64 upperBound,
                                  std::size_t n) -> i64 {
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
