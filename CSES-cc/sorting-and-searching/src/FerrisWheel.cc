#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <utility>    // IWYU pragma: keep
#include <vector>     // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _FerrisWheel {

auto run() -> void {
  int n, x;
  std::cin >> n >> x;

  std::vector<int> p(n);
  for (int i = 0; i < n; i++) {
    std::cin >> p[i];
  }

  std::sort(p.begin(), p.end());

  int l{}, r{n - 1}, cnt{};
  while (l <= r) {
    if (l == r) [[unlikely]] {
      cnt += 1;
      break;
    }

    if (p[r] + p[l] <= x) {
      l += 1;
      r -= 1;
      cnt += 1;
    } else {
      r -= 1;
      cnt += 1;
    }
  }

  std::cout << cnt << "\n";
}

}  // namespace _FerrisWheel

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
    _FerrisWheel::run();

  std::cout.flush();

  return 0;
}
