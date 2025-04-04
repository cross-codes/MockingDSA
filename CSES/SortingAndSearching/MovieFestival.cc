#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 200000;
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

  std::size_t n;
  std::cin >> n;

  for (std::size_t i = 0; i < n; i++) {
    u32 a, b;
    std::cin >> a >> b;
    ::array[i] = {a, b};
  }

  std::sort(&::array[0], &::array[n], PAIR_ORDER);

  u32 cnt = 1U, nextStart = ::array[0].second;
  for (std::size_t i = 1; i < n; i++) {
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
