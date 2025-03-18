#include <cmath>
#include <cstring>
#include <functional>
#include <memory>
#include <vector>

class Solution
{
private:
  inline static constexpr int maxN = 10000;

  constexpr inline static int ceilLog2(std::int64_t n)
  {
    return (n == 1) ? 1 : 64 - __builtin_clzll(n - 1);
  }

  template <typename T> struct SegmentTree
  {
    /*
     * Author: github.com/cross-codes
     */

  private:
    std::size_t offset_;
    std::unique_ptr<T[]> tree_;

    std::function<T(const T &, const T &)> function_;
    T defaultValue_;

  public:
    template <std::size_t N>
    SegmentTree(const std::array<T, N> &array, T defaultValue,
                std::function<T(const T &, const T &)> function)
        : offset_(1LL << ceilLog2(N)),
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

    void setAtIndex(std::size_t index, T value)
    {
      index += offset_;
      tree_[index] = value;

      while (index != 1)
      {
        tree_[index >> 1] = function_(tree_[index], tree_[index ^ 1]);
        index >>= 1;
      }
    }

    T queryRange(std::size_t fromIdx, std::size_t pastEndIdx)
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

public:
  int lengthOfLIS(std::vector<int> &a)
  {
    std::array<int, (maxN << 1) + 1> tree{};

    auto MAX_SELECT = [&](const int &a, const int &b) {
      return std::max(a, b);
    };

    auto segmentTree{SegmentTree<int>(tree, 0, MAX_SELECT)};

    int n = static_cast<int>(a.size());
    std::unique_ptr<int[]> d(new int[n]);
    d[0] = 1;
    segmentTree.setAtIndex(a[0] + maxN, 1);

    for (int i = 1; i < n; i++)
    {
      d[i] = std::max(1, segmentTree.queryRange(0, a[i] + maxN) + 1);
      segmentTree.setAtIndex(a[i] + maxN, d[i]);
    }

    int maxLength{};
    for (int i = 0; i < n; i++)
      maxLength = std::max(maxLength, d[i]);

    return maxLength;
  }
};
