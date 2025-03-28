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
  SegmentTree(const std::unique_ptr<T[]> &array, std::size_t n, T defaultValue,
              std::function<T(const T &, const T &)> function)
      : offset_(1LL << Algebra::ceil_log2(n)),
        tree_(std::make_unique<T[]>(offset_ << 1)), function_(function),
        defaultValue_(defaultValue)
  {
    std::copy(&array[0], &array[n], &tree_[offset_]);

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

  template <std::size_t N>
  SegmentTree(const std::array<T, N> &array, T defaultValue,
              std::function<T(const T &, const T &)> function)
      : offset_(1LL << Algebra::ceil_log2(N)),
        tree_(std::make_unique<T[]>(offset_ << 1)), function_(function),
        defaultValue_(defaultValue)
  {
    std::copy(array.begin(), array.end(), &tree_[offset_]);

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

  T query_range(std::size_t fromIdx, std::size_t pastEndIdx)
  {
    fromIdx += offset_, pastEndIdx += offset_;

    T result{defaultValue_};
    while (fromIdx < pastEndIdx)
    {
      if (fromIdx & 1)
        result = function_(result, tree_[fromIdx++]);
      if (pastEndIdx & 1)
        result = function_(result, tree_[--pastEndIdx]);

      fromIdx >>= 1, pastEndIdx >>= 1;
    }

    return result;
  }
};
