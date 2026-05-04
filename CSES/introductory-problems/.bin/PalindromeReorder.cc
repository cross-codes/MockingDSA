#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <string>     // IWYU pragma: keep
#include <unordered_map>
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

#ifdef AZURELIGHT
#include <sys/resource.h>
#endif

namespace _PalindromeReorder {

auto run() -> void {
  std::string s;
  std::cin >> s;

  int len = static_cast<int>(s.size());

  std::unordered_map<char, int> freq{};
  for (char c : s) {
    freq[c] += 1;
  }

  int num_odd = 0;
  for (const auto& [k, v] : freq) {
    if (v & 1)
      num_odd += 1;
  }

  if (len & 1) {
    std::vector<char> res(len, '?');
    if (num_odd != 1) {
      std::cout << "NO SOLUTION\n";
      return;
    } else {
      char odd{};
      int l{}, r{len - 1};
      for (auto& [k, v] : freq) {
        if (v & 1) {
          res[len >> 1] = k;
          odd           = k;
        } else {
          while (v != 0) {
            res[l] = k;
            res[r] = k;
            l += 1;
            r -= 1;
            v -= 2;
          }
        }
      }

      for (char c : res) {
        if (c != '?')
          std::cout << c;
        else
          std::cout << odd;
      }
      std::cout << "\n";
    }
  } else {
    std::vector<char> res(len);
    if (num_odd != 0) {
      std::cout << "NO SOLUTION\n";
      return;
    } else {
      int l{}, r{len - 1};
      for (auto& [k, v] : freq) {
        while (v != 0) {
          res[l] = k;
          res[r] = k;
          l += 1;
          r -= 1;
          v -= 2;
        }
      }
    }

    for (char c : res)
      std::cout << c;
    std::cout << "\n";
  }
}

}  // namespace _PalindromeReorder

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
    _PalindromeReorder::run();

  std::cout.flush();

#ifdef AZURELIGHT
  std::fclose(stdin);
#endif

  return 0;
}
