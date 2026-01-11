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

namespace _BuildingTeams {

enum Colour { GRAY, BLUE, RED };

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> adj(n);
  for (int i = 0, a, b; i < m; i++) {
    std::cin >> a >> b;
    adj[a - 1].push_back(b - 1);
    adj[b - 1].push_back(a - 1);
  }

  std::vector<Colour> colour(n, Colour::GRAY);

  auto invert = [&](Colour c) -> Colour {
    return (c == Colour::BLUE ? Colour::RED : Colour::BLUE);
  };

  bool possible = true;

  auto dfs      = [&colour, &invert, &adj, &possible](auto&& dfs, int u,
                                                 int p) -> void {
    if (p == -1) {
      colour[u] = Colour::BLUE;
    } else {
      colour[u] = invert(colour[p]);
    }

    for (int e : adj[u]) {
      if (colour[e] == Colour::GRAY) {
        dfs(dfs, e, u);
      } else if (colour[e] == colour[u]) {
        possible = false;
      }
    }
  };

  for (int i = 0; i < n; i++) {
    if (colour[i] == Colour::GRAY) {
      dfs(dfs, i, -1);
    }
  }

  if (!possible) {
    std::cout << "IMPOSSIBLE\n";
    return;
  }

  for (int i = 0; i < n; i++) {
    std::cout << (colour[i] == Colour::BLUE ? 1 : 2) << " ";
  }

  std::cout << "\n";
}

}  // namespace _BuildingTeams

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
    _BuildingTeams::run();

  std::cout.flush();

  return 0;
}
