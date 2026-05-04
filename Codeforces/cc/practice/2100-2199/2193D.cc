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
#include <numeric>
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

namespace _2193D {

class StaticPrefixSum {
 private:
  std::vector<int64_t> prefix_;

 public:
  StaticPrefixSum(const std::vector<int>& array) {
    prefix_ = std::vector<int64_t>(array.size() + 1);
    for (size_t i = 1; i <= array.size(); i++) {
      prefix_[i] = prefix_[i - 1] + array[i - 1];
    }
  }

  StaticPrefixSum(const std::vector<int64_t>& array) {
    prefix_ = std::vector<int64_t>(array.size() + 1);
    for (size_t i = 1; i <= array.size(); i++) {
      prefix_[i] = prefix_[i - 1] + array[i - 1];
    }
  }

  auto range_sum(int a, int b) -> int64_t { return prefix_[b] - prefix_[a]; }
};

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  for (int i = 0; i < n; i++) {
    std::cin >> b[i];
  }

  std::sort(a.begin(), a.end());

  StaticPrefixSum prefix(b);

  auto score = [&](int from) -> int64_t {
    auto pred = [&](int m) -> bool {
      return prefix.range_sum(0, m) > n - from;
    };

    int L{0}, R{n + 1};
    while (R - L > 1) {
      int M             = std::midpoint(L, R);
      (pred(M) ? R : L) = M;
    }

    return static_cast<int64_t>(a[from]) * L;
  };

  int64_t mx{INT64_MIN};
  for (int i = 0; i < n; i++) {
    mx = std::max(mx, score(i));
  }

  std::cout << mx << "\n";
}

}  // namespace _2193D

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
    _2193D::run();

  std::cout.flush();

  return 0;
}
