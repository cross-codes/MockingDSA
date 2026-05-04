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

namespace _F {

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<std::tuple<int64_t, int64_t, int64_t>> f(n);
  for (int i = 0, a, b, c; i < n; i++) {
    std::cin >> a >> b >> c;
    f[i] = {a, b, c};
  }

  std::vector<std::vector<int>> adj(n), adjR(n);

  for (int i = 0; i < n; i++) {
    auto& [ai, bi, ci] = f[i];
    for (int j = 0; j < n; j++) {
      auto& [aj, bj, cj] = f[j];
      int64_t a = ai - aj, b = bi - bj, c = ci - cj;
      if ((b * b - 4 * a * c) < 0 || (a == 0 && b == 0 && c != 0)) {
        if (ci < cj) {
          adj[i].push_back(j);
          adjR[j].push_back(i);
        } else {
          adj[j].push_back(i);
          adjR[i].push_back(j);
        }
      }
    }
  }

  std::vector<int> lo(n, -1), li(n, -1);

  auto dfs = [&](auto&& dfs, int u) -> int {
    if (lo[u] != -1) {
      return lo[u];
    }

    int mx{};
    for (auto v : adj[u]) {
      mx = std::max(mx, dfs(dfs, v));
    }

    return lo[u] = mx + 1;
  };

  auto dfsR = [&](auto&& dfs, int u) -> int {
    if (li[u] != -1) {
      return li[u];
    }

    int mx{};
    for (auto v : adjR[u]) {
      mx = std::max(mx, dfs(dfs, v));
    }

    return li[u] = mx + 1;
  };

  for (int i = 0; i < n; i++) {
    dfs(dfs, i);
    dfsR(dfsR, i);
  }

  for (int i = 0; i < n; i++) {
    std::cout << lo[i] + li[i] - 1 << " ";
  }

  std::cout << "\n";
}

}  // namespace _F

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
  std::cin >> t;
  while (t-- > 0)
    _F::run();

  std::cout.flush();

  return 0;
}
