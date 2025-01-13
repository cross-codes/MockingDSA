#include <cstdint>
#include <cstddef>

struct FenwickTree {
private:
  size_t N;
  int64_t *tree;

public:
  int64_t *array;

  FenwickTree(size_t n)
      : N(n), tree(new int64_t[n + 1]), array(new int64_t[n + 1]) {};

  void add(size_t k, int64_t x) {
    while (k <= N) {
      tree[k] += x;
      k += (k == 0 ? 0 : 1 << __builtin_ctzl(k));
    }
  }

  int64_t sumq(size_t k) {
    int64_t s = 0LL;
    while (k >= 1) {
      s += tree[k];
      k -= (k == 0 ? 0 : 1 << __builtin_ctzl(k));
    }
    return s;
  }
};
