#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <unordered_map>
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _CollectingNumbers {

auto run() -> void {
  int n;
  std::cin >> n;

  std::unordered_map<int, int> pos{};
  pos.reserve(200000);
  int mx{};
  for (int i = 1, x; i <= n; i++) {
    std::cin >> x;
    pos[x] = i;
    mx     = std::max(mx, x);
  }

  int cur{1}, cnt{1}, idx{pos[cur]};
  while (cur < mx) {
    while (cur < mx && pos[cur + 1] > idx) {
      idx = pos[cur + 1];
      cur += 1;
    }

    if (cur != mx && pos[cur + 1] < idx) {
      idx = pos[cur + 1];
      cur += 1;
      cnt += 1;
    }
  }

  std::cout << cnt << "\n";
}

}  // namespace _CollectingNumbers

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
    _CollectingNumbers::run();

  std::cout.flush();

  return 0;
}
