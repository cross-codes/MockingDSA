#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <set>
#include <string>   // IWYU pragma: keep
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

#ifdef AZURELIGHT
#include <sys/resource.h>
#endif

namespace _ConcertTickets {

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::multiset<int> h{};

  for (int i = 0, x; i < n; i++) {
    std::cin >> x;
    h.insert(x);
  }

  for (int i = 0, t; i < m; i++) {
    std::cin >> t;
    auto it = h.upper_bound(t);
    if (it == h.begin()) {
      std::cout << "-1\n";
    } else {
      auto back = std::prev(it);
      std::cout << *back << "\n";
      h.erase(back);
    }
  }
}

}  // namespace _ConcertTickets

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef AZURELIGHT
  const rlim_t stack_size = 268435456;
  struct rlimit rl;

  int result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0 && rl.rlim_cur < stack_size) {
    rl.rlim_cur = stack_size;
    result      = setrlimit(RLIMIT_STACK, &rl);
    if (result != 0)
      std::cerr << "WARN: setrlimit failed\n";
  }

  FILE* stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  while (t-- > 0)
    _ConcertTickets::run();

  std::cout.flush();

#ifdef AZURELIGHT
  std::fclose(stdin);
#endif

  return 0;
}
