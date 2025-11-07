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

#ifdef AZURELIGHT
#include <sys/resource.h>
#endif

namespace _TwoSets {

auto run() -> void {
  int64_t n;
  std::cin >> n;

  if (n * (n + 1) % 4 != 0) {
    std::cout << "NO\n";
  } else {
    int64_t target = n * (n + 1) / 4;
    std::vector<int64_t> set1, set2;
    set1.reserve(n), set2.reserve(n);
    int64_t sum1{};

    for (int64_t i = n; i >= 1; i--) {
      if (sum1 + i <= target) {
        set1.push_back(i);
        sum1 += i;
      } else {
        set2.push_back(i);
      }
    }

    std::cout << "YES\n" << set1.size() << "\n";
    for (const int64_t& e : set1)
      std::cout << e << " ";

    std::cout << set2.size() << "\n";
    for (const int64_t& e : set2)
      std::cout << e << " ";

    std::cout << "\n";
  }
}

}  // namespace _TwoSets

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
    _TwoSets::run();

  std::cout.flush();

#ifdef AZURELIGHT
  std::fclose(stdin);
#endif

  return 0;
}
