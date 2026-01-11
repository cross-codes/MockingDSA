#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <concepts>   // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <deque>      // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <map>        // IWYU pragma: keep
#include <memory>     // IWYU pragma: keep
#include <queue>
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

namespace _MessageRoute {

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> adj(n);
  for (int i = 0, a, b; i < m; i++) {
    std::cin >> a >> b;
    adj[a - 1].push_back(b - 1);
    adj[b - 1].push_back(a - 1);
  }

  std::vector<int> parent(n, -1), distance(n, INT_MAX);
  distance[0] = 1;

  std::vector<bool> visited(n, false);
  std::queue<int> queue{};
  visited[0] = true;
  queue.push(0);
  while (!queue.empty()) {
    int s = queue.front();
    queue.pop();
    for (int e : adj[s]) {
      if (!visited[e]) {
        parent[e]   = s;
        visited[e]  = true;
        distance[e] = distance[s] + 1;
        queue.push(e);
      }
    }
  }

  if (parent[n - 1] == -1) {
    std::cout << "IMPOSSIBLE\n";
    return;
  }

  std::vector<int> trace{};
  std::cout << distance[n - 1] << "\n";
  int curr = n - 1;
  trace.push_back(curr);
  while (parent[curr] != -1) {
    int next = parent[curr];
    trace.push_back(next);
    curr = next;
  }

  int sz = static_cast<int>(trace.size());
  for (int i = sz - 1; i >= 0; i--) {
    std::cout << trace[i] + 1 << " ";
  }

  std::cout << "\n";
}

}  // namespace _MessageRoute

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
    _MessageRoute::run();

  std::cout.flush();

  return 0;
}
