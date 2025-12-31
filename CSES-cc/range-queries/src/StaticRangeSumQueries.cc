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

namespace _StaticRangeSumQueries {

class StaticPrefixSum {
 private:
  std::vector<int64_t> prefix;

 public:
  StaticPrefixSum(const std::vector<int>& array) {
    prefix = std::vector<int64_t>(array.size() + 1);
    for (size_t i = 1; i <= array.size(); i++) {
      prefix[i] = prefix[i - 1] + array[i - 1];
    }
  }

  StaticPrefixSum(const std::vector<int64_t>& array) {
    prefix = std::vector<int64_t>(array.size() + 1);
    for (size_t i = 1; i <= array.size(); i++) {
      prefix[i] = prefix[i - 1] + array[i - 1];
    }
  }

  auto range_sum(int a, int b) -> int64_t { return prefix[b] - prefix[a]; }
};

auto run() -> void {
  int n, q;
  std::cin >> n >> q;

  std::vector<int> x(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
  }

  StaticPrefixSum prefix(x);

  for (int i = 0, a, b; i < q; i++) {
    std::cin >> a >> b;
    std::cout << prefix.range_sum(a - 1, b) << "\n";
  }
}

}  // namespace _StaticRangeSumQueries

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
    _StaticRangeSumQueries::run();

  std::cout.flush();

  return 0;
}
