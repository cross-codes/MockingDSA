#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <concepts>   // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <deque>
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

namespace _SlidingWindowMinimum {

class BarrettReducer {
 private:
  uint64_t mod, m;

 public:
  BarrettReducer(uint64_t mod) : mod(mod), m(UINT64_C(-1) / mod) {}

  auto reduce(uint64_t a) -> uint64_t {
    uint64_t v = a - (uint64_t)((__uint128_t(m) * a) >> 64) * mod;
    return v >= mod ? v - mod : v;
  }
};

auto run() -> void {
  int n, k, c;
  std::cin >> n >> k;

  int64_t x0, a, b;
  std::cin >> x0 >> a >> b >> c;

  BarrettReducer reducer(c);

  std::vector<int> x(n);
  x[0] = static_cast<int>(x0);
  for (int i = 1; i < n; i++) {
    x[i] = static_cast<int>(reducer.reduce(a * x[i - 1] + b));
  }

  std::deque<int> deque{};
  for (int i = 0; i < k; i++) {
    while (!deque.empty() && deque.back() > x[i]) {
      deque.pop_back();
    }

    deque.push_back(x[i]);
  }

  int64_t res = deque.front();
  for (int i = k; i < n; i++) {
    if (x[i - k] == deque.front()) {
      deque.pop_front();
    }

    while (!deque.empty() && deque.back() > x[i]) {
      deque.pop_back();
    }

    deque.push_back(x[i]);
    res ^= deque.front();
  }

  std::cout << res << "\n";
}

}  // namespace _SlidingWindowMinimum

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
    _SlidingWindowMinimum::run();

  std::cout.flush();

  return 0;
}
