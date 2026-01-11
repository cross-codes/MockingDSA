#include <algorithm>      // IWYU pragma: keep
#include <array>          // IWYU pragma: keep
#include <bit>            // IWYU pragma: keep
#include <cassert>        // IWYU pragma: keep
#include <cmath>          // IWYU pragma: keep
#include <concepts>       // IWYU pragma: keep
#include <cstdint>        // IWYU pragma: keep
#include <cstring>        // IWYU pragma: keep
#include <deque>          // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <map>            // IWYU pragma: keep
#include <memory>         // IWYU pragma: keep
#include <set>            // IWYU pragma: keep
#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <utility>        // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _ForestQueries {

class Prefix2DGenerator {
 private:
  std::vector<std::vector<int>> prefix_2D;

 public:
  Prefix2DGenerator(const std::vector<std::vector<int>>& grid) {
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());

    prefix_2D.resize(n, std::vector<int>(m, 0));

    std::vector<std::vector<int>> vpsinc(m, std::vector<int>(n));
    for (int x = 0; x < m; x++)
      for (int y = 0; y < n; y++) {
        if (y == 0)
          vpsinc[x][y] = grid[y][x];
        else
          vpsinc[x][y] = vpsinc[x][y - 1] + grid[y][x];
      }

    for (int y = 0; y < n; y++)
      prefix_2D[y][0] = vpsinc[0][y];

    for (int y = 0; y < n; y++)
      for (int x = 1; x < m; x++)
        prefix_2D[y][x] = prefix_2D[y][x - 1] + vpsinc[x][y];
  }

  int sum_region(int y1, int x1, int y2, int x2) {
    int ax = x2, ay = y2;
    int bx = x1, by = y2;
    int cx = x2, cy = y1;
    int dx = x1, dy = y1;

    int res{prefix_2D[ay][ax]};

    if (bx > 0)
      res -= prefix_2D[by][bx - 1];

    if (cy > 0)
      res -= prefix_2D[cy - 1][cx];

    if (dx > 0 && dy > 0)
      res += prefix_2D[dy - 1][dx - 1];

    return res;
  }
};

auto run() -> void {
  int n, q;
  std::cin >> n >> q;

  std::vector<std::vector<int>> grid(n, std::vector<int>(n));
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < n; x++) {
      char c;
      std::cin >> c;
      grid[y][x] = (c == '.' ? 0 : 1);
    }
  }

  Prefix2DGenerator prefix(grid);

  for (int i = 0, y1, x1, y2, x2; i < q; i++) {
    std::cin >> y1 >> x1 >> y2 >> x2;
    std::cout << prefix.sum_region(y1 - 1, x1 - 1, y2 - 1, x2 - 1) << "\n";
  }
}

}  // namespace _ForestQueries

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef EVERMORE
  pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);

  FILE* stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  while (t-- > 0)
    _ForestQueries::run();

  std::cout.flush();

  return 0;
}
