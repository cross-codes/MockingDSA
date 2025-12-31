#include <algorithm>      // IWYU pragma: keep
#include <array>          // IWYU pragma: keep
#include <bit>            // IWYU pragma: keep
#include <cassert>        // IWYU pragma: keep
#include <cmath>          // IWYU pragma: keep
#include <cstdint>        // IWYU pragma: keep
#include <cstring>        // IWYU pragma: keep
#include <deque>          // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <utility>        // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _SubarraySumsI {

auto run() -> void {
  int n, x;
  std::cin >> n >> x;

  std::unordered_map<int64_t, int> prefix_store{};
  prefix_store[0] = 1;

  std::vector<int64_t> prefix(n + 1);
  int64_t res{};
  for (int i = 1, a; i <= n; i++) {
    std::cin >> a;
    prefix[i] = prefix[i - 1] + a;
    res += prefix_store[prefix[i] - x];
    prefix_store[prefix[i]] += 1;
  }

  std::cout << res << "\n";
}

}  // namespace _SubarraySumsI

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
    _SubarraySumsI::run();

  std::cout.flush();

  return 0;
}
