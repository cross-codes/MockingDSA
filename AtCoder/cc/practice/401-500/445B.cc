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

namespace _445B {

auto run() -> void {
  int N;
  std::cin >> N;

  std::vector<std::string> s(N);
  size_t m{};
  for (int i = 0; i < N; i++) {
    std::cin >> s[i];
    m = std::max(m, s[i].size());
  }

  for (int i = 0; i < N; i++) {
    auto n = s[i].size();
    auto k = (m - n) >> 1;
    for (auto j = 0UZ; j < k; j++) {
      std::cout << ".";
    }

    std::cout << s[i];

    for (auto j = 0UZ; j < k; j++) {
      std::cout << ".";
    }

    std::cout << "\n";
  }
}

}  // namespace _445B

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
    _445B::run();

  std::cout.flush();

  return 0;
}
