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

namespace _HotelQueries {

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
  int n, m;
  std::cin >> n >> m;

  std::vector<int> h(n);
  for (int i = 0; i < n; i++) {
    std::cin >> h[i];
  }

  SegmentTree tree(h, INT_MIN, std::ranges::max);

  auto pred = [&](int q, int v) -> bool {
    int f = tree.range_query(0, q);
    return f >= v;
  };

  for (int i = 0, r; i < m; i++) {
    std::cin >> r;

    int L{-1}, R{n + 1};
    while (R - L > 1) {
      int M                = std::midpoint(L, R);
      (pred(M, r) ? R : L) = M;
    }

    if (R == n + 1) {
      std::cout << "0 ";
    } else {
      std::cout << R << " ";
      tree.set_at_index(R - 1, tree.range_query(0, R) - r);
    }
  }
}

}  // namespace _HotelQueries

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
    _HotelQueries::run();

  std::cout.flush();

  return 0;
}
