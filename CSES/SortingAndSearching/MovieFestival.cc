#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 200000;
std::pair<u32, u32> array[_];

constexpr auto PAIR_ORDER = [](std::pair<u32, u32> a,
                               std::pair<u32, u32> b) -> bool {
  if (a.second < b.second)
    return true;
  else if (a.second == b.second)
    return a.first < b.first;
  else
    return false;
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  std::cin >> n;

  for (size_t i = 0; i < n; i++) {
    u32 a, b;
    std::cin >> a >> b;
    ::array[i] = {a, b};
  }

  std::sort(&::array[0], &::array[n], PAIR_ORDER);

  u32 cnt = 1U, nextStart = ::array[0].second;
  for (size_t i = 1; i < n; i++) {
    auto elem = ::array[i];
    if (elem.first < nextStart)
      continue;
    else {
      cnt++;
      nextStart = elem.second;
    }
  }

  std::cout << cnt << "\n";

  return 0;
}
