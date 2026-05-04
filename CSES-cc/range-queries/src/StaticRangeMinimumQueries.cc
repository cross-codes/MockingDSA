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

namespace _StaticRangeMinimumQueries {

template <typename T, typename Op>
  requires std::invocable<Op, T, T>
struct IdempotentSparseTable {
 private:
  [[no_unique_address]] Op function_;
  std::vector<std::vector<T>> table_;
  std::size_t n_;

 public:
  IdempotentSparseTable(Op func, const std::vector<T>& array)
      : function_(func), n_(array.size()) {
    std::size_t K = std::bit_width(n_) - 1;

    table_.resize(K + 1, std::vector<T>(n_));
    std::copy(array.begin(), array.end(), table_[0].begin());

    for (std::size_t y = 1; y < table_.size(); y++)
      for (std::size_t x = 0, k = 1 << (y - 1); x <= n_ - (1 << y); x++, k++)
        table_[y][x] = function_(table_[y - 1][x], table_[y - 1][k]);
  }

  T range_query(std::size_t a, std::size_t b) {
    std::size_t row = std::bit_width(b - a) - 1;
    return function_(table_[row][a], table_[row][b - (1 << row)]);
  }
};

auto run() -> void {
  int n, q;
  std::cin >> n >> q;

  std::vector<int> x(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
  }

  IdempotentSparseTable table(std::ranges::min, x);

  for (int i = 0, a, b; i < q; i++) {
    std::cin >> a >> b;
    std::cout << table.range_query(a - 1, b) << "\n";
  }
}

}  // namespace _StaticRangeMinimumQueries

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
    _StaticRangeMinimumQueries::run();

  std::cout.flush();

  return 0;
}
