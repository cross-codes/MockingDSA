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

// Edge case
namespace _E {

auto run() -> void {
  int k;
  std::cin >> k;

  if (k == 0) {
    std::cout << 0 << "\n";
    return;
  } else if (k == 1) {
    std::cout << "2\n0 0\n0 1\n";
    return;
  } else if (k == 2) {
    std::cout << "3\n0 0\n0 1\n1 0\n";
    return;
  }

  int64_t mx{};
  for (int i = 2; i < 501; i++) {
    if ((i * (i - 1) >> 1) > k) {
      mx = i - 1;
      break;
    }
  }

  std::vector<std::string> points{};

  for (int i = 0; i < mx; i++) {
    points.push_back(std::format("0 {}", i));
  }

  int64_t rem = k - ((mx * (mx - 1)) >> 1);
  for (int i = 2; i < 501; i++) {
    if ((i * (i - 1) >> 1) > rem) {
      mx = i - 1;
      break;
    }
  }

  for (int i = 0; i < mx; i++) {
    points.push_back(std::format("{} 20000", i + 1));
  }

  rem -= (mx * (mx - 1) >> 1);

  for (int i = 0; i < rem; i++) {
    points.push_back(std::format("{} {}", -(i + 1), (i + 1)));
  }

  std::cout << points.size() << "\n";
  for (auto& s : points) {
    std::cout << s << "\n";
  }
}

}  // namespace _E

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
    _E::run();

  std::cout.flush();

  return 0;
}
