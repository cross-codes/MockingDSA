#include <climits>
#include <cstdint>
#include <cstring>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 1000;
i64 grid[_][_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    size_t n, m;
    std::cin >> n >> m;

    std::string path;
    std::cin >> path;

    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < m; j++)
        std::cin >> grid[i][j];
    }

    size_t x = 0, y = 0;
    for (char c : path) {
      if (c == 'D') {
        i64 sum = 0;
        for (size_t j = 0; j < m; j++)
          sum += grid[x][j];
        grid[x][y] = -sum;
        ++x;
      } else {
        i64 sum = 0;
        for (size_t i = 0; i < n; i++)
          sum += grid[i][y];
        grid[x][y] = -sum;
        ++y;
      }
    }

    i64 sum = 0;
    for (size_t j = 0; j < m; j++)
      sum += grid[n - 1][j];

    grid[n - 1][m - 1] = -sum;

    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < m; j++)
        std::cout << grid[i][j] << " ";
      std::cout << "\n";
    }
  }

  return 0;
}
