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

namespace _ShortestRoutesI {

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> adj(n);
  for (int i = 0, a, b, c; i < m; i++) {
    std::cin >> a >> b >> c;
    adj[a - 1].emplace_back(b - 1, c);
  }

  std::vector<bool> processed(n, false);
  std::vector<int64_t> distance(n, 9223372036854775807LL);

  std::priority_queue<std::pair<int64_t, int>> queue{};
  distance[0] = 0;
  queue.emplace(INT64_C(0), 0);
  while (!queue.empty()) {
    int a = queue.top().second;
    queue.pop();

    if (processed[a]) {
      continue;
    }

    processed[a] = true;
    for (auto& [b, w] : adj[a]) {
      if (distance[a] + w < distance[b]) {
        distance[b] = distance[a] + w;
        queue.emplace(-distance[b], b);
      }
    }
  }

  for (int64_t e : distance) {
    std::cout << e << " ";
  }

  std::cout << "\n";
}

}  // namespace _ShortestRoutesI

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
    _ShortestRoutesI::run();

  std::cout.flush();

  return 0;
}
