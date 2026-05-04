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

namespace _ShortestRoutesII {

auto run() -> void {
  int n, m, q;
  std::cin >> n >> m >> q;

  std::vector<std::vector<int>> adjM(n, std::vector<int>(n, INT_MAX));
  for (int i = 0, a, b, c; i < m; i++) {
    std::cin >> a >> b >> c;
    adjM[a - 1][b - 1] = std::min(c, adjM[a - 1][b - 1]);
    adjM[b - 1][a - 1] = std::min(c, adjM[a - 1][b - 1]);
  }

  std::vector<std::vector<int64_t>> distance(
      n, std::vector<int64_t>(n, INT64_MAX >> 2));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        distance[i][j] = 0;
      } else if (adjM[i][j] != INT_MAX) {
        distance[i][j] = adjM[i][j];
      }
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        distance[i][j] =
            std::min(distance[i][j], distance[i][k] + distance[k][j]);
      }
    }
  }

  for (int i = 0, a, b; i < q; i++) {
    std::cin >> a >> b;
    std::cout << (distance[a - 1][b - 1] == INT64_MAX >> 2
                      ? -1
                      : distance[a - 1][b - 1])
              << "\n";
  }
}

}  // namespace _ShortestRoutesII

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
    _ShortestRoutesII::run();

  std::cout.flush();

  return 0;
}
