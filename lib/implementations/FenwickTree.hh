#include <cstddef>
#include <cstdint>
#include <memory>

struct FenwickTree {
private:
  size_t N_;
  std::unique_ptr<int64_t[]> tree_;

public:
  std::unique_ptr<int64_t[]> array;

  FenwickTree(size_t n)
      : N_(n), tree_(std::make_unique<int64_t[]>(n + 1)),
        array(std::make_unique<int64_t[]>(n + 1)) {};

  void addToIndex(size_t k, int64_t x) {
    while (k <= N_) {
      tree_[k] += x;
      k += (k == 0 ? 0 : 1 << __builtin_ctzll(k));
    }
  }

  int64_t prefixSumAt(size_t k) {
    int64_t s = 0LL;
    while (k >= 1) {
      s += tree_[k];
      k -= (k == 0 ? 0 : 1 << __builtin_ctzll(k));
    }
    return s;
  }
};
