#include <algorithm>
#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 200000;
std::pair<i64, i64> tasks[_];

constexpr auto PAIR_ORDER = [](std::pair<i64, i64> a,
                               std::pair<i64, i64> b) -> bool {
  return a.first < b.first;
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  std::cin >> n;

  for (std::size_t i = 0; i < n; i++) {
    i64 duration, deadline;
    std::cin >> duration >> deadline;
    ::tasks[i] = {duration, deadline};
  }

  std::sort(&::tasks[0], &::tasks[n], ::PAIR_ORDER);

  i64 currentTime = 0LL, currentScore = 0LL;
  for (std::size_t i = 0; i < n; i++) {
    auto [duration, deadline] = tasks[i];
    currentTime += duration;
    currentScore += deadline - currentTime;
  }

  std::cout << currentScore << "\n";

  return 0;
}
