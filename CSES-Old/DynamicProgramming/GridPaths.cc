#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 1001;
constexpr int MOD = static_cast<int>(1e9 + 7);

int grid[_][_], numPaths[_][_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  std::cin >> n;

  for (std::size_t y = 1; y <= n; y++) {
    for (std::size_t x = 1; x <= n; x++) {
      char c;
      std::cin >> c;
      if (c == '.')
        ::grid[y][x] = 1;
      else
        ::grid[y][x] = -1;
    }
  }

  ::numPaths[1][1] = 1;
  for (std::size_t y = 1; y <= n; y++) {
    for (std::size_t x = 1; x <= n; x++) {

      if (grid[y][x] == -1) [[unlikely]] {
        ::numPaths[y][x] = 0;
        continue;
      }

      if (::grid[y - 1][x] == 1)
        ::numPaths[y][x] += ::numPaths[y - 1][x];

      if (::grid[y][x - 1] == 1)
        ::numPaths[y][x] += ::numPaths[y][x - 1];

      ::numPaths[y][x] %= ::MOD;
    }
  }

  std::cout << numPaths[n][n] << "\n";

  return 0;
}
