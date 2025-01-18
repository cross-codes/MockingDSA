#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    int n, m;
    std::cin >> n >> m;

    std::pair<int, int> upRightPrev;
    std::pair<int, int> bottomLeftCurrent;
    i64 perimeter = 0;
    bool once = true;
    while (n-- > 0) {
      int x, y;
      std::cin >> x >> y;
      if (once) {
        upRightPrev = {x + m, y + m};
        bottomLeftCurrent = {x, y};
        perimeter += 4 * m;
        once = false;
      } else {
        bottomLeftCurrent.first += x;
        bottomLeftCurrent.second += y;
        perimeter -= upRightPrev.first - bottomLeftCurrent.first +
                     upRightPrev.second - bottomLeftCurrent.second;
        perimeter += 2 * m +
                     (m - (upRightPrev.first - bottomLeftCurrent.first)) +
                     (m - (upRightPrev.second - bottomLeftCurrent.second));
        upRightPrev = {bottomLeftCurrent.first + m,
                       bottomLeftCurrent.second + m};
      }
    }

    std::cout << perimeter << "\n";
  }

  return 0;
}
