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

namespace _ArrayDescription {

constexpr int MOD = 1000000007;

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> x(n + 1, -1);
  for (int i = 1; i <= n; i++) {
    std::cin >> x[i];
  }

  std::array<std::array<int64_t, 101>, 100001> count{};
  if (x[1] == 0) {
    for (int i = 1; i <= m; i++) {
      count[1][i] = 1;
    }
  } else {
    count[1][x[1]] = 1;
  }

  for (int i = 2; i <= n; i++) {
    if (x[i] != 0) {
      count[i][x[i]] = count[i - 1][x[i]];

      if (x[i] > 1) {
        count[i][x[i]] += count[i - 1][x[i] - 1];
      }

      if (x[i] < m) {
        count[i][x[i]] += count[i - 1][x[i] + 1];
      }

      count[i][x[i]] %= MOD;
    } else {
      for (int j = 1; j <= m; j++) {
        count[i][j] += count[i - 1][j];

        if (j != 1) {
          count[i][j] += count[i - 1][j - 1];
        }

        if (j != m) {
          count[i][j] += count[i - 1][j + 1];
        }

        count[i][j] %= MOD;
      }
    }
  }

  int64_t total{};
  for (int i = 1; i <= m; i++) {
    total += count[n][i];
  }

  std::cout << total % MOD << "\n";
}

}  // namespace _ArrayDescription

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
    _ArrayDescription::run();

  std::cout.flush();

  return 0;
}
