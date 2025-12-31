#include <concepts>
#include <bit>
#include <vector>

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
