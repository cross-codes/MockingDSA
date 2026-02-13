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
#include <numeric>
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

namespace _2189C {

auto run() -> void {
  size_t n;
  std::cin >> n;

  std::vector<size_t> p(n, 0);
  p[n - 1] = 1;

  for (size_t i = 1; i <= n - 2; i++) {
    p[i] = (i + 1) ^ 1;
  }

  p[0] = (n * (n + 1) >> 1) - std::accumulate(p.begin(), p.end(), INT64_C(0));

  for (auto e : p) {
    std::cout << e << " ";
  }

#ifdef EVERMORE
  std::unordered_set<size_t> seen{};
  for (auto e : p) {
    seen.insert(e);
  }
  assert(seen.size() == n);
#endif

  std::cout << "\n";
}

}  // namespace _2189C

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
    _2189C::run();

  std::cout.flush();

  return 0;
}
