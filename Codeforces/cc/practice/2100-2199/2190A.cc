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

namespace _2190A {

auto run() -> void {
  int n;
  std::cin >> n;

  std::string s;
  std::cin >> s;

  std::string s_sorted = s;

  std::sort(s_sorted.begin(), s_sorted.end());

  if (s == s_sorted) {
    std::cout << "Bob\n";
    return;
  }

  std::vector<int> pos{};

  for (int i = 0; i < n; i++) {
    if (s[i] != s_sorted[i]) {
      pos.push_back(i + 1);
    }
  }

  std::cout << "Alice\n" << pos.size() << "\n";

  for (int e : pos) {
    std::cout << e << " ";
  }

  std::cout << "\n";
}

}  // namespace _2190A

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
  std::cin >> t;
  while (t-- > 0)
    _2190A::run();

  std::cout.flush();

  return 0;
}
