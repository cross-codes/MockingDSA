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

namespace _444D {

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

class DifferenceArray {
 private:
  std::vector<int64_t> diff;
  SegmentTree<int64_t, decltype(std::plus<int64_t>())> tree;

 public:
  static std::vector<int64_t> compute_diff(const std::vector<int64_t>& array) {
    std::vector<int64_t> diff(array.size() + 1);
    diff[0] = array[0];
    for (size_t i = 1; i < array.size(); i++) {
      diff[i] = array[i] - array[i - 1];
    }
    return diff;
  }

  DifferenceArray(const std::vector<int64_t>& array)
      : diff(compute_diff(array)),
        tree(diff, INT64_C(0), std::plus<int64_t>()) {}

  void increase_in_range(std::size_t a, std::size_t b, int x) {
    tree.set_at_index(a, diff[a] + x);
    diff[a] += x;

    tree.set_at_index(b, diff[b] - x);
    diff[b] -= x;
  }

  auto get_underlying_value(std::size_t index) -> int64_t {
    return tree.range_query(0, index + 1);
  }
};

auto run() -> void {
  int N;
  std::cin >> N;

  std::vector<int> a(N);
  int mx{INT_MIN};
  for (int i = 0; i < N; i++) {
    std::cin >> a[i];
    mx = std::max(mx, a[i]);
  }

  std::vector<int64_t> u(200001, 0);
  DifferenceArray diff(u);

  for (int i = 0; i < N; i++) {
    diff.increase_in_range(0, a[i], 1);
  }

  std::string res{};
  int64_t carry{};
  for (int i = 0; i < mx; i++) {
    int64_t under = diff.get_underlying_value(i);
    int64_t val   = under + carry;
    res += std::to_string(val % 10);
    carry = val / 10;
  }

  while (carry > 0) {
    res += std::to_string(carry % 10);
    carry /= 10;
  }

  std::reverse(res.begin(), res.end());

  std::cout << res << "\n";
}

}  // namespace _444D

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
    _444D::run();

  std::cout.flush();

  return 0;
}
