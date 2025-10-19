#include <functional>
#include <memory>

#include "util/Algebra.hh"

template <typename T> struct SegmentTree
{
private:
  std::size_t offset_;
  std::unique_ptr<T[]> tree_;

  std::function<T(const T &, const T &)> function_;
  T defaultValue_;

public:
  SegmentTree(T array[], std::size_t n, T default_value,
              std::function<T(const T &, const T &)> function)
      : offset_(1LL << Algebra::ceil_log2(n)),
        tree_(std::make_unique<T[]>(offset_ << 1)), function_(function),
        defaultValue_(default_value)
  {
    std::copy(array, array + n, &tree_[offset_]);

    std::size_t i = offset_;
    while (i != 1)
    {
      std::size_t j = i;
      while (j < i << 1)
      {
        tree_[j >> 1] = function_(tree_[j], tree_[j + 1]);
        j += 2;
      }
      i >>= 1;
    }
  }

  void set_at_index(std::size_t index, T value)
  {
    index += offset_;
    tree_[index] = value;

    while (index != 1)
    {
      tree_[index >> 1] = function_(tree_[index], tree_[index ^ 1]);
      index >>= 1;
    }
  }

  T query_range(std::size_t from_idx, std::size_t past_end_idx)
  {
    from_idx += offset_, past_end_idx += offset_;

    T result{defaultValue_};
    while (from_idx < past_end_idx)
    {
      if (from_idx & 1)
        result = function_(result, tree_[from_idx++]);
      if (past_end_idx & 1)
        result = function_(result, tree_[--past_end_idx]);

      from_idx >>= 1, past_end_idx >>= 1;
    }

    return result;
  }
};
