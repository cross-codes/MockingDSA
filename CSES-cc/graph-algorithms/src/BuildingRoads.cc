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

namespace _BuildingRoads {

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> adj(n);
  for (int i = 0, a, b; i < m; i++) {
    std::cin >> a >> b;
    adj[a - 1].push_back(b - 1);
    adj[b - 1].push_back(a - 1);
  }

  std::vector<bool> visited(n);

  auto dfs = [&visited, &adj](auto&& dfs, int u) -> void {
    visited[u] = true;
    for (int e : adj[u]) {
      if (!visited[e]) {
        dfs(dfs, e);
      }
    }
  };

  std::vector<int> comp_rep{};
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      comp_rep.push_back(i);
      dfs(dfs, i);
    }
  }

  std::cout << comp_rep.size() - 1 << "\n";
  for (size_t i = 0; i < comp_rep.size() - 1; i++) {
    std::cout << comp_rep[i] + 1 << " " << comp_rep[i + 1] + 1 << "\n";
  }
}

}  // namespace _BuildingRoads

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
    _BuildingRoads::run();

  std::cout.flush();

  return 0;
}
