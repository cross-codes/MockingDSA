#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <bitset>
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

namespace _HighScore {

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> adj(n), adjT(n);
  std::vector<std::tuple<int, int, int>> edges(m);
  for (int i = 0, a, b, x; i < m; i++) {
    std::cin >> a >> b >> x;
    adj[a - 1].push_back({b - 1, -x});
    adjT[b - 1].push_back({a - 1, -x});
    edges.push_back({a - 1, b - 1, -x});
  }

  std::bitset<2500> visited;
  auto dfs = [&adj, &visited](auto&& dfs, int u) -> void {
    visited.set(u, true);
    for (const auto& [v, _] : adj[u]) {
      if (!visited[v]) {
        dfs(dfs, v);
      }
    }
  };

  dfs(dfs, 0);

  std::bitset<2500> visitedT;
  auto dfsR = [&adjT, &visitedT](auto&& dfsR, int u) -> void {
    visitedT.set(u, true);
    for (const auto& [v, _] : adjT[u]) {
      if (!visitedT[v]) {
        dfsR(dfsR, v);
      }
    }
  };

  dfsR(dfsR, n - 1);

  std::bitset<2500> valid = visited & visitedT;
  std::vector<int64_t> distance(n, INT64_MAX >> 2);
  distance[0] = 0;
  for (int i = 1; i < n; i++) {
    for (const auto& [a, b, x] : edges) {
      if (valid[a] && valid[b]) {
        distance[b] = std::min(distance[b], distance[a] + x);
      }
    }
  }

  for (const auto& [a, b, x] : edges) {
    if (valid[a] && valid[b] && distance[b] > distance[a] + x) {
      std::cout << "-1\n";
      return;
    }
  }

  std::cout << -distance[n - 1] << "\n";
}

}  // namespace _HighScore

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
    _HighScore::run();

  std::cout.flush();

  return 0;
}
