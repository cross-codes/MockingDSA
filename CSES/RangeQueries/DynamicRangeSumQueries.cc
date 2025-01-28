#include <cstdint>
#include <iostream>
#include <memory>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

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

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n, q;
  std::cin >> n >> q;

  FenwickTree bit(n);

  for (size_t i = 1; i <= n; i++) {
    i64 num;
    std::cin >> num;
    bit.addToIndex(i, num);
    bit.array[i] = num;
  }

  while (q-- > 0) {
    u32 choice;
    std::cin >> choice;
    if (choice == 1) {
      size_t k;
      i64 u;
      std::cin >> k >> u;
      bit.addToIndex(k, u - bit.array[k]);
      bit.array[k] = u;
    } else {
      size_t a, b;
      std::cin >> a >> b;
      std::cout << (bit.prefixSumAt(b) - bit.prefixSumAt(a - 1)) << "\n";
    }
  }

  return 0;
}
