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

namespace _Repetitions {

auto run() -> void {
  std::string s;
  std::cin >> s;

  int n         = static_cast<int>(s.size());
  char cur_char = s[0];
  int mx{}, cnt{1};

  for (int i = 1; i < n; i++) {
    if (cur_char != s[i]) {
      cur_char = s[i];
      mx       = std::max(mx, cnt);
      cnt      = 1;
    } else {
      cnt += 1;
    }
  }

  std::cout << std::max(mx, cnt) << "\n";
}

}  // namespace _Repetitions

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
    _Repetitions::run();

  std::cout.flush();

#ifdef AZURELIGHT
  std::fclose(stdin);
#endif

  return 0;
}
