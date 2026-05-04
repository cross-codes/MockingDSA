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

namespace _PalindromeReorder {

auto run() -> void {
  std::string s;
  std::cin >> s;
  int n = static_cast<int>(s.size());

  std::string res{};
  res.resize(s.size());

  std::array<int, 26> freq{};
  for (char c : s) {
    freq[c - 'A'] += 1;
  }

  int odd_pos{}, odd_freq{-1};
  for (int i = 0; i < 26; i++) {
    int e = freq[i];
    if (e & 1) {
      if (odd_freq != -1) {
        std::cout << "NO SOLUTION\n";
        return;
      } else {
        odd_pos  = i;
        odd_freq = e;
      }
    }
  }

  if (n & 1) {
    if (odd_freq == -1) {
      std::cout << "NO SOLUTION\n";
      return;
    }

    int l{}, r{n - 1};
    for (int i = 0; i < 26; i++) {
      if (i == odd_pos) [[unlikely]] {
        continue;
      }

      int e = freq[i];
      for (int j = 0; j < e; j += 2) {
        res[l++] = static_cast<char>(i + 'A');
        res[r--] = static_cast<char>(i + 'A');
      }
    }

    for (int j = l; j <= r; j++) {
      res[j] = static_cast<char>(odd_pos + 'A');
    }
  } else {
    if (odd_freq != -1) {
      std::cout << "NO SOLUTION\n";
      return;
    }

    int l{}, r{n - 1};
    for (int i = 0; i < 26; i++) {
      int e = freq[i];
      for (int j = 0; j < e; j += 2) {
        res[l++] = static_cast<char>(i + 'A');
        res[r--] = static_cast<char>(i + 'A');
      }
    }
  }

  std::cout << res << "\n";
}

}  // namespace _PalindromeReorder

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
    _PalindromeReorder::run();

  std::cout.flush();

  return 0;
}
