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

// Jesus
namespace _C {

auto run() -> void {
  uint32_t n, x;
  std::cin >> n >> x;

  std::vector<uint32_t> res;
  res.reserve(n);

  auto can_push = [&](uint32_t u) -> bool { return (u & x) == u; };

  auto match    = [&]() -> bool {
    uint32_t or_res{};
    for (auto e : res) {
      or_res |= e;
    }

    return or_res == x;
  };

  auto mex = [&]() -> uint32_t {
    std::array<bool, 200001> seen{};
    for (auto e : res) {
      if (e < 200001) {
        seen[e] = true;
      }
    }

    for (int i = 0; i < 200001; i++) {
      if (!seen[i]) {
        return i;
      }
    }

    __builtin_unreachable();
  };

  for (int i = 0; i < 2e5; i++) {
    if (res.size() == n) {
      break;
    }

    if (can_push(i)) {
      res.push_back(i);
    }
  }

  if (!match()) {
    res.pop_back();
    res.push_back(x);
  }

  uint32_t start = mex();

  while (res.size() < n) {
    if (can_push(start)) {
      res.push_back(start);
    } else {
      break;
    }
    start += 1;
  }

  while (res.size() < n) {
    res.push_back(0);
  }

  for (auto e : res) {
    std::cout << e << " ";
  }

  std::cout << "\n";
}

}  // namespace _C

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
    _C::run();

  std::cout.flush();

  return 0;
}
