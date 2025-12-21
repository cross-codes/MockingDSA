#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <climits>
#include <cmath>     // IWYU pragma: keep
#include <cstdint>   // IWYU pragma: keep
#include <cstring>   // IWYU pragma: keep
#include <iostream>  // IWYU pragma: keep
#include <string>    // IWYU pragma: keep
#include <utility>   // IWYU pragma: keep
#include <vector>    // IWYU pragma: keep

#ifdef AZURELIGHT
#include <sys/resource.h>
#endif

namespace _MovieFestival {

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> intervals(n);
  for (int i = 0, s, e; i < n; i++) {
    std::cin >> s >> e;
    intervals[i] = {s, e};
  }

  auto SORT_ORDER = [](const std::pair<int, int>& a,
                       const std::pair<int, int>& b) -> bool {
    if (a.second == b.second) {
      return a.first < b.first;
    }
    return a.second < b.second;
  };

  std::sort(intervals.begin(), intervals.end(), SORT_ORDER);

  int lend{INT_MIN}, cnt{};
  for (const auto& [s, e] : intervals) {
    if (s >= lend) {
      cnt += 1;
      lend = e;
    }
  }

  std::cout << cnt << "\n";
}

}  // namespace _MovieFestival

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
    _MovieFestival::run();

  std::cout.flush();

#ifdef AZURELIGHT
  std::fclose(stdin);
#endif

  return 0;
}
