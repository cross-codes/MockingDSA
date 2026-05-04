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

namespace _D {

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<__int128_t> f(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    int64_t x;
    std::cin >> x;
    f[i] = x;
  }

  std::vector<__int128_t> a(n + 1, 0);
  for (int i = 2; i < n; i++) {
    a[i] = (f[i - 1] - (f[i] << 1) + f[i + 1]) >> 1;
  }

  __int128_t f1 = f[1];
  for (int i = 2; i < n; i++) {
    f1 -= (a[i] * std::abs(i - 1));
  }

  a[n]          = f1 / (n - 1);

  __int128_t fn = f[n];
  for (int i = 2; i < n; i++) {
    fn -= (a[i] * std::abs(i - n));
  }

  a[1] = fn / (n - 1);

  for (int i = 1; i <= n; i++) {
    std::cout << static_cast<int>(a[i]) << " ";
  }

  std::cout << "\n";
}

}  // namespace _D

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
    _D::run();

  std::cout.flush();

  return 0;
}
