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

namespace _GridColoringI {

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> grid(n);
  for (int y = 0; y < n; y++) {
    std::cin >> grid[y];
  }

  std::array<char, 4> choices = {'A', 'B', 'C', 'D'};
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      char curr{grid[y][x]};
      char left{(x > 0 ? grid[y][x - 1] : '#')},
          up{(y > 0 ? grid[y - 1][x] : '#')};

      bool set{};
      for (char c : choices) {
        if (c != curr && c != left && c != up) {
          grid[y][x] = c;
          set        = true;
          break;
        }
      }

      if (!set) {
        std::cout << "IMPOSSIBLE\n";
        return;
      }
    }
  }

  for (int y = 0; y < n; y++) {
    std::cout << grid[y] << "\n";
  }
}

}  // namespace _GridColoringI

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
    _GridColoringI::run();

  std::cout.flush();

  return 0;
}
