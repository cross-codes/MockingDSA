#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <concepts>   // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <deque>      // IWYU pragma: keep
#include <functional>
#include <iostream>  // IWYU pragma: keep
#include <map>       // IWYU pragma: keep
#include <memory>    // IWYU pragma: keep
#include <set>       // IWYU pragma: keep
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

namespace _SlidingWindowOr {

template <typename F, typename T>
  requires std::invocable<F, T, T>
class AggregateQueue {
 private:
  struct AggregateStack {
   public:
    std::stack<std::pair<T, T>> stack;

    AggregateStack() {}

    void push(T x) {
      T curr_agg = stack.empty() ? x : F()(stack.top().second, x);
      stack.push(std::make_pair(x, curr_agg));
    }

    void pop() { stack.pop(); }

    auto aggregate() -> T { return stack.top().second; }
  };

  AggregateStack in, out;

 public:
  AggregateQueue() {}

  void push_back(T x) { in.push(x); }

  void pop_front() {
    if (out.stack.empty()) {
      while (!in.stack.empty()) {
        T val = in.stack.top().first;
        in.pop();
        out.push(val);
      }
    }
    out.pop();
  }

  auto query() -> T {
    if (in.stack.empty())
      return out.aggregate();

    if (out.stack.empty())
      return in.aggregate();

    return F()(in.aggregate(), out.aggregate());
  }
};

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

  AggregateQueue<std::bit_or<int>, int> agg{};

  for (int i = 0; i < k; i++) {
    agg.push_back(x[i]);
  }

  int res = agg.query();
  for (int i = k; i < n; i++) {
    agg.pop_front();
    agg.push_back(x[i]);
    res ^= agg.query();
  }

  std::cout << res << "\n";
}

}  // namespace _SlidingWindowOr

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
    _SlidingWindowOr::run();

  std::cout.flush();

  return 0;
}
