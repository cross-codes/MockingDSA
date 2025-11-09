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

namespace _CreatingStrings {

constexpr std::array<int, 9> FACTORIAL = {1,   1,   2,    6,    24,
                                          120, 720, 5040, 40320};

auto run() -> void {
  std::string s;
  std::cin >> s;

  std::array<int, 26> freq{};
  for (char& c : s) {
    freq[c - 'a'] += 1;
  }

  auto next_permutation = [&s]() -> bool {
    auto r_first = std::make_reverse_iterator(s.end());
    auto r_last  = std::make_reverse_iterator(s.begin());
    auto left    = std::is_sorted_until(r_first, r_last);

    if (left != r_last) {
      auto right = std::upper_bound(r_first, left, *left);
      std::iter_swap(left, right);
    }

    std::reverse(left.base(), s.end());
    return left != r_last;
  };

  int permutations = FACTORIAL[s.size()];
  for (int& f : freq) {
    permutations /= FACTORIAL[f];
  }

  std::cout << permutations << "\n";
  std::sort(s.begin(), s.end());
  do {
    std::cout << s << "\n";
  } while (next_permutation());
}

}  // namespace _CreatingStrings

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
    _CreatingStrings::run();

  std::cout.flush();

#ifdef AZURELIGHT
  std::fclose(stdin);
#endif

  return 0;
}
