#include <cmath>
#include <cstring>
#include <functional>
#include <memory>
#include <vector>

class NumArray {
private:
  std::size_t offset_;
  std::unique_ptr<int[]> tree_;

  std::function<int(const int &, const int &)> function_;
  int defaultValue_;

  int ceilLog2_(std::int64_t n) {
    return (n == 1) ? 1 : 64 - __builtin_clzll(n - 1);
  }

public:
  NumArray(std::vector<int> &nums)
      : offset_(1LL << ceilLog2_(nums.size())), defaultValue_(0) {
    tree_ = std::make_unique<int[]>(offset_ << 1);
    function_ = [&](const int &a, const int &b) { return a + b; };

    std::copy(nums.begin(), nums.end(), &tree_[offset_]);

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

  void update(int index, int val) {
    index += offset_;
    tree_[index] = val;

    while (index != 1) {
      tree_[index >> 1] = function_(tree_[index], tree_[index ^ 1]);
      index >>= 1;
    }
  }

  int sumRange(int left, int right) {
    left += offset_, right += offset_ + 1;

    int result{defaultValue_};
    while (left < right) {
      if (left & 1)
        result = function_(result, tree_[left++]);
      if (right & 1)
        result = function_(result, tree_[--right]);

      left >>= 1, right >>= 1;
    }

    return result;
  }
};
