#include <cstdint>
#include <vector>

struct FenwickTree {
private:
  std::vector<int64_t> tree;
  size_t N;

public:
  std::vector<int64_t> array;

  FenwickTree(size_t n) : tree(n + 1), N(n), array(n + 1) {};

  void add(size_t k, int64_t x) {
    while (k <= this->N) {
      this->tree[k] += x;
      k += (k == 0 ? 0 : 1 << __builtin_ctzl(k));
    }
  }

  int64_t sumq(size_t k) {
    int64_t s = 0LL;
    while (k >= 1) {
      s += this->tree[k];
      k -= (k == 0 ? 0 : 1 << __builtin_ctzl(k));
    }
    return s;
  }
};
