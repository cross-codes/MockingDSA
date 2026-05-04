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

namespace _DynamicRangeMinimumQueries {

template <typename T, typename Op>
  requires std::invocable<Op, T, T>
class SegmentTree {
 private:
  std::size_t n_, offset_;
  std::vector<T> tree_;

  [[no_unique_address]] Op function_;
  T default_value_;

 public:
  SegmentTree(std::vector<T> array, T default_value, Op function)
      : n_(array.size()), function_(function), default_value_(default_value) {
    offset_ = std::size_t(1) << std::bit_width(n_ - 1);
    tree_.assign(offset_ << 1, default_value_);
    std::copy(array.begin(), array.end(), tree_.begin() + offset_);

    std::size_t i = offset_;
    while (i != 1) {
      std::size_t j = i;
      while (j < i << 1) {
        tree_[j >> 1] = function_(tree_[j], tree_[j + 1]);
        j += 2;
      }
      i >>= 1;
    }
  }

  void set_at_index(std::size_t index, T value) {
    index += offset_;
    tree_[index] = value;

    while (index != 1) {
      tree_[index >> 1] = function_(tree_[index], tree_[index ^ 1]);
      index >>= 1;
    }
  }

  [[nodiscard]] auto range_query(std::size_t a, std::size_t b) const -> T {
    a += offset_, b += offset_;

    T result{default_value_};
    while (a < b) {
      if (a & 1)
        result = function_(result, tree_[a++]);
      if (b & 1)
        result = function_(result, tree_[--b]);

      a >>= 1, b >>= 1;
    }

    return result;
  }
};

auto run() -> void {
  int n, q;
  std::cin >> n >> q;

  std::vector<int64_t> x(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
  }

  SegmentTree tree(x, INT64_MAX, std::ranges::min);

  for (int i = 0, c, k, u, a, b; i < q; i++) {
    std::cin >> c;
    if (c == 1) {
      std::cin >> k >> u;
      tree.set_at_index(k - 1, u);
    } else {
      std::cin >> a >> b;
      std::cout << tree.range_query(a - 1, b) << "\n";
    }
  }
}

}  // namespace _DynamicRangeMinimumQueries

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
    _DynamicRangeMinimumQueries::run();

  std::cout.flush();

  return 0;
}
