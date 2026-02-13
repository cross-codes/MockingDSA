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

namespace _FlightDiscount {

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> adj(n), adjT(n);
  std::vector<std::tuple<int, int, int>> edges(m);
  for (int i = 0, a, b, c; i < m; i++) {
    std::cin >> a >> b >> c;
    adj[a - 1].emplace_back(b - 1, c);
    adjT[b - 1].emplace_back(a - 1, c);
    edges.emplace_back(a - 1, b - 1, c);
  }

  std::vector<bool> processed(n);
  std::vector<int64_t> distance1(n, INT64_MAX >> 2);

  std::priority_queue<std::pair<int64_t, int>> queue1{};
  distance1[0] = 0;
  queue1.emplace(0, 0);
  while (!queue1.empty()) {
    auto [_, a] = queue1.top();
    queue1.pop();
    if (processed[a]) {
      continue;
    }

    processed[a] = true;
    for (const auto& [b, w] : adj[a]) {
      if (distance1[a] + w < distance1[b]) {
        distance1[b] = distance1[a] + w;
        queue1.emplace(-distance1[b], b);
      }
    }
  }

  std::fill(processed.begin(), processed.end(), false);
  std::vector<int64_t> distanceN(n, INT64_MAX >> 2);

  std::priority_queue<std::pair<int64_t, int>> queue2{};
  distanceN[n - 1] = 0;
  queue2.emplace(0, n - 1);
  while (!queue2.empty()) {
    auto [_, a] = queue2.top();
    queue2.pop();
    if (processed[a]) {
      continue;
    }

    processed[a] = true;
    for (const auto& [b, w] : adjT[a]) {
      if (distanceN[a] + w < distanceN[b]) {
        distanceN[b] = distanceN[a] + w;
        queue2.emplace(-distanceN[b], b);
      }
    }
  }

  int64_t mn{INT64_MAX};
  for (const auto& [a, b, c] : edges) {
    int64_t new_dist = distance1[a] + (c >> 1) + distanceN[b];
    mn               = std::min(mn, new_dist);
  }

  std::cout << mn << "\n";
}

}  // namespace _FlightDiscount

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
    _FlightDiscount::run();

  std::cout.flush();

  return 0;
}
