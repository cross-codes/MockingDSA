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

namespace _2185D {

auto run() -> void {
  int n, m, h;
  std::cin >> n >> m >> h;

  std::vector<int64_t> a(n + 1), inc(n + 1), mxd(n + 1), gen(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    mxd[i] = h - a[i];
  }

  int cur_gen{};
  for (int i = 0, b, c; i < m; i++) {
    std::cin >> b >> c;
    if (gen[b] < cur_gen) {
      inc[b] = c;
      gen[b] = cur_gen;
    } else {
      inc[b] += c;
    }

    if (inc[b] > mxd[b]) {
      cur_gen += 1;
    }
  }

  for (int i = 1; i <= n; i++) {
    std::cout << a[i] + ((gen[i] == cur_gen) ? inc[i] : 0) << " ";
  }

  std::cout << "\n";
}

}  // namespace _2185D

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
    _2185D::run();

  std::cout.flush();

  return 0;
}
