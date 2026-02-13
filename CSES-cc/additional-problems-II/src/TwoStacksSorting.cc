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
#include <stack>
#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <utility>        // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _TwoStacksSorting {

constexpr int SENTINEL{0x3f3f3f3f};

auto run() -> void {
  int n, nxt{1};
  std::cin >> n;

  std::stack<int> a{}, b{};
  a.push(SENTINEL);
  b.push(SENTINEL);
  std::vector<int> order{};
  for (int i = 0, x; i < n; i++) {
    std::cin >> x;
    if (a.top() < x && b.top() < x) {
      std::cout << "IMPOSSIBLE\n";
      return;
    }

    if (a.top() >= b.top()) {
      if (x < a.top()) {
        a.push(x);
        order.push_back(1);
      } else {
        b.push(x);
        order.push_back(2);
      }
    } else {
      if (x < b.top()) {
        b.push(x);
        order.push_back(2);
      } else {
        a.push(x);
        order.push_back(1);
      }
    }

    if (x == nxt) {
      while (a.top() == nxt || b.top() == nxt) {
        if (a.top() == nxt) {
          a.pop();
          nxt += 1;
        }

        if (b.top() == nxt) {
          b.pop();
          nxt += 1;
        }
      }
    }
  }

  for (int e : order) {
    std::cout << e << " ";
  }

  std::cout << "\n";
}

}  // namespace _TwoStacksSorting

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
    _TwoStacksSorting::run();

  std::cout.flush();

  return 0;
}
