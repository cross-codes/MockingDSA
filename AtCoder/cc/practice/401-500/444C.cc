#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <concepts>   // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <deque>      // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <map>        // IWYU pragma: keep
#include <memory>     // IWYU pragma: keep
#include <set>        // IWYU pragma: keep
#include <span>
#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <utility>        // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _444C {

auto run() -> void {
  int N;
  std::cin >> N;

  std::vector<int> a(N);
  for (int i = 0; i < N; i++) {
    std::cin >> a[i];
  }

  std::sort(a.begin(), a.end());
  auto it        = std::lower_bound(a.begin(), a.end(), a.back());
  auto idx       = std::distance(a.begin(), it);

  auto can_split = [](std::span<int> v, int expected) -> bool {
    if (v.size() % 2 != 0) {
      return false;
    }

    int l = 0, r = static_cast<int>(v.size()) - 1;
    while (l < r) {
      if (v[l] + v[r] != expected) {
        return false;
      }

      l += 1;
      r -= 1;
    }

    return true;
  };

  std::span<int> full(a);

  auto mx_ign = full.subspan(0, idx);
  if (can_split(mx_ign, a.back())) {
    std::cout << a.back() << "\n";
  }

  if (can_split(full, a.front() + a.back())) {
    std::cout << a.front() + a.back() << " ";
  }
}

}  // namespace _444C

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
    _444C::run();

  std::cout.flush();

  return 0;
}
