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

namespace _TrailingZeroes {

auto run() -> void {
  int n;
  std::cin >> n;

  int res{}, div{5};
  while (div <= n) {
    res += n / div;
    div *= 5;
  }

  std::cout << res << "\n";
}

}  // namespace _TrailingZeroes

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
    _TrailingZeroes::run();

  std::cout.flush();

#ifdef AZURELIGHT
  std::fclose(stdin);
#endif

  return 0;
}
